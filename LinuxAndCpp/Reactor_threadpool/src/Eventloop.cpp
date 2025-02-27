#include "../include/EventLoop.h"

#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>

using std::cerr;
using std::cout;

EventLoop::EventLoop(Acceptor & acceptor)
:_epfd(createEpollFd())
,_evtList(1024)
,_isLooping(false)
,_acceptor(acceptor)
,_evtfd(createEventFd())
,_mutex()
{
    int listenfd = acceptor.getFd();
    addEpollReadFd(listenfd);

    addEpollReadFd(_evtfd);
}

EventLoop::~EventLoop()
{
    close(_epfd);
    close(_evtfd);
}

void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    if(_isLooping)
    {
        _isLooping = false;
    }
}

void EventLoop::waitEpollFd()
{
    int n_ready = 0;
    do
    {
        n_ready = epoll_wait(_epfd,&*_evtList.begin(),_evtList.size(),3000);
    }while (n_ready == -1 && errno == EINTR);

    if(n_ready == -1)
    {
        cerr<<"n_ready == -1\n";
        return;
    }
    else if(n_ready == 0)
    {
        cout<<"epoll_wait timeout\n";
    }
    else
    {
        //判断文件描述符数量是不是达到上限，上限需要扩容
        if(n_ready == (int)_evtList.size())
        {
            //扩容两倍
            _evtList.reserve(2 * n_ready);
        }
        //遍历就绪集合 进行业务逻辑处理
        for(int i = 0;i<n_ready;++i)
        {
            int fd = _evtList[i].data.fd;
            //查看就绪集合里的文件描述符是不是listenfd
            if(fd == _acceptor.getFd())
            {
                if(_evtList[i].events & EPOLLIN)
                {
                    //处理新的连接
                    handleNewConnection();
                }
            }
            //就绪集合里是用于通信的文件描述符
            else if(fd == _evtfd)
            {
                if(_evtList[i].events & EPOLLIN)
                {
                    handleRead();
                    //执行所有待执行的任务
                    doPendings();
                }
            }
            else
            {
                if(_evtList[i].events & EPOLLIN)
                {
                    //处理老的连接
                    handleMessage(fd);
                }
            }
        }
    }
}

void EventLoop::handleNewConnection()
{
    int connfd = _acceptor.accept();
    if(connfd < 0)
    {
        perror("EventLoop::handleNewConnection");
        return;
    }

    addEpollReadFd(connfd);

    TcpConnectionPtr con(new TcpConnection(connfd,this));

    //将三个回调函数注册给TcpConnection
    con->setNewConnectionCallback(_onNewConnectionCb);
    con->setMessageCallback(_onMessageCb);
    con->setCloseCallback(_onCloseCb);

    //以键值对方式存储
    _conns[connfd] = con;

    con->handleNewConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    if(it != _conns.end())
    {
        //连接存在,可以进行数据收发
        bool flag = it->second->isClosed();
        if(flag)
        {
            //如果连接断开
            it->second->handleCloseCallback();
            delEpollReadFd(fd);
            _conns.erase(it);
        }
        else
        {
            it->second->handleMessageCallback();
        }
    }
    else
    {
        cout<<"连接不存在\n";
        return;
    }
}

int EventLoop::createEpollFd()
{
    int fd = ::epoll_create(100);
    if(fd < 0)
    {
        perror("EventLoop::createEpollFd");
    }

    return fd;
}

void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt; 
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = ::epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&evt);
    if(ret < 0)
    {
        perror("EventLoop::addEpollReadFd");
        return;
    }
}

void EventLoop::delEpollReadFd(int fd)
{
    int ret = ::epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,nullptr);
    if(ret < 0)
    {
        perror("EventLoop::delEpollReadFd");
        return;
    }
}

void EventLoop::setNewConnectionCallback(TcpConnectionCallback && cb)
{
    _onNewConnectionCb = std::move(cb);
}

void EventLoop::setMessageCallback(TcpConnectionCallback && cb)
{
    _onMessageCb = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback && cb)
{
    _onCloseCb = std::move(cb);
}

void EventLoop::handleRead()
{
    uint64_t two;
    ssize_t ret = read(_evtfd,&two,sizeof(uint64_t));
    if(ret != sizeof(uint64_t))
    {
        perror("EventLoop::handleRead read");
        return;
    }
}

void EventLoop::doPendings()
{
    vector<Functor> temp;
    
    {
        //锁的粒度(锁的范围)
        MutexLockGuard auto_lock(_mutex);
        temp.swap(_pendings);
    }

    for(auto & cb:temp)
    {
        //回调执行任务
        cb();
    }
}

int EventLoop::createEventFd()
{
    int fd = eventfd(10,0);
    if(fd < 0)
    {
        perror("EventLoop::createEventFd eventfd");
    }

    return fd;
}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t ret = write(_evtfd,&one,sizeof(uint64_t));
    if(ret!=sizeof(uint64_t))
    {
        perror("EventLoop::wakeup write");
        return;
    }
}

void EventLoop::runInLoop(Functor && cb)
{
    {
        //锁的粒度(锁的范围)
        MutexLockGuard auto_lock(_mutex);
        _pendings.push_back(std::move(cb));
    }

    //只要将"任务"传递给EventLoop/Reactor之后,就应该通知EventLoop/Reacotr
    wakeup();
}
