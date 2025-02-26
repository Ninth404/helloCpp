#include "../include/TcpConnection.h"

#include <sstream>
#include <iostream>

using std::cout;
using std::ostringstream;

TcpConnection::TcpConnection(int fd,EventLoop *loop)
:_loop(loop)
,_socketIO(fd)
,_socket(fd)
,_localAddr(getLocalAddr())
,_peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::send(const string & msg)
{
    _socketIO.writen(msg.c_str(),msg.size());
}

void TcpConnection::sendInLoop(const string & msg)
{
    if(_loop)
    {
        // TODO
        // _loop->runInLoop(std::bind(&TcpConnection::send,this,msg));
    }
}

string TcpConnection::receive()
{
    char buf[65535] = {0};
    _socketIO.readLine(buf,sizeof(buf));

    return string(buf);
}

bool TcpConnection::isClosed() const
{
    char buf[10] = {0};
    int ret = ::recv(_socket.getFd(),buf,sizeof(buf),MSG_PEEK);
    
    return (ret == 0);
}

string TcpConnection::toString()
{
    ostringstream oss;

    oss<<_localAddr.getIp()<<":"
        <<_localAddr.getPort()<<"--->"
        <<_peerAddr.getIp()<<":"
        <<_peerAddr.getPort();

    return oss.str();
}

InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //获取本端地址的函数getsockname
    int ret = getsockname(_socket.getFd(),(struct sockaddr *)&addr,&len);
    if(ret == -1)
    {
        perror("TcpConnection::getLocalAddr");
    }

    return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //获取对端地址的函数getpeername
    int ret = getpeername(_socket.getFd(),(struct sockaddr *)&addr,&len);
    if(ret == -1)
    {
        perror("TcpConnection::getPeerAddr");
    }

    return InetAddress(addr);
}

//三个回调函数注册
void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback &cb)
{
    _onNewConnectionCb = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
    _onMessageCb = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
    _onCloseCb = cb;
}

//三个回调的执行
void TcpConnection::handleNewConnectionCallback()
{
    if(_onNewConnectionCb)
    {
        _onNewConnectionCb(shared_from_this());
    }
    else
    {
        cout << "_onNewConnectionCb == nullptr" << "\n";
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessageCb)
    {
        _onMessageCb(shared_from_this());
    }
    else
    {
        cout << "_onMessageCb == nullptr" << "\n";
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onCloseCb)
    {
        _onCloseCb(shared_from_this());
    }
    else
    {
        cout<<"_onCloseCb == nullptr"<<"\n";
    }
}