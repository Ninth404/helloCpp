#ifndef __EVENT_LOOP_H__
#define __EVENT_LOOP_H__

#include "../include/Acceptor.h"
#include "../include/TcpConnection.h"
#include "../include/MutexLock.h"

#include <vector>
#include <map>
#include <functional>

using std::vector;
using std::map;
using std::function;

using Functor = function<void()>;

class EventLoop
{
public:
    EventLoop(Acceptor & acceptor);
    ~EventLoop();

    //设置循环与否
    void loop();
    void unloop();

private:
    //封装epoll_wait函数
    void waitEpollFd();

    //处理新连接
    void handleNewConnection();

    //处理老连接上消息的到达
    void handleMessage(int fd);

    //epfd创建
    int createEpollFd();

    //监听文件的描述符
    void addEpollReadFd(int fd);

    //取消文件描述符的监听
    void delEpollReadFd(int fd);
public:
    void setNewConnectionCallback(TcpConnectionCallback &&cb);//连接到来注册
    void setMessageCallback(TcpConnectionCallback &&cb);//消息到达注册
    void setCloseCallback(TcpConnectionCallback &&cb);//连接关闭注册
private:
    void handleRead();
    void doPendings();
    int createEventFd();
public:
    void wakeup();
    void runInLoop(Functor && cb);
private:
    int _epfd;  // epoll_create 创建的文件描述符
    vector<struct epoll_event> _evtList; //就绪队列 ： 存放满足条件的文件描述符 
    bool _isLooping; //标志事件循环是否在运行的标志
    Acceptor & _acceptor; // 调用其中的accept函数
    map<int,TcpConnectionPtr> _conns;//存放文件描述符与连接的键值对

    TcpConnectionCallback _onNewConnectionCb; //连接建立
    TcpConnectionCallback _onMessageCb; //消息道达
    TcpConnectionCallback _onCloseCb; //连接断开

    int _evtfd;//用于通信的文件描述符
    vector<Functor> _pendings;//待执行的任务
    MutexLock _mutex; //互斥访问共享资源vector
    
};

#endif