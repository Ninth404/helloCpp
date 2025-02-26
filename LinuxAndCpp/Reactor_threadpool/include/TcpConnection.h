#ifndef __TCP_CONNECTION_H__
#define __TCP_CONNECTION_H__

#include "../include/SocketIO.h"
#include "../include/Socket.h"
#include "../include/InetAddress.h"

#include <memory>
#include <functional>

using std::shared_ptr;
using std::function;

class TcpConnection;
class EventLoop;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    explicit TcpConnection(int fd,EventLoop *loop);
    ~TcpConnection();
    void send(const string & msg);
    void sendInLoop(const string & msg);
    string receive();
    bool isClosed() const;

    //测试函数
    string toString();

    //三个事件回调注册
    void setNewConnectionCallback(const TcpConnectionCallback & cb);
    void setMessageCallback(const TcpConnectionCallback & cb);
    void setCloseCallback(const TcpConnectionCallback & cb);

    //三个事件回调执行
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
private:
    EventLoop * _loop;
    SocketIO _socketIO;

    //为了调试而加入的三个数据成员
    Socket _socket;
    InetAddress _localAddr;
    InetAddress _peerAddr;

    //三个事件数据成员
    TcpConnectionCallback _onNewConnectionCb;//连接建立
    TcpConnectionCallback _onMessageCb;//消息到达
    TcpConnectionCallback _onCloseCb;//连接断开
};

#endif