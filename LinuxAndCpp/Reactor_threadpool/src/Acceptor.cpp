#include "../include/Acceptor.h"

Acceptor::Acceptor(const string &ip,unsigned short port)
:_socket()
,_addr(ip,port)
{

}

Acceptor::~Acceptor()
{

}

void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

void Acceptor::setReuseAddr()
{
    int on = 1;
    int ret = setsockopt(_socket.getFd(),SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(ret)
    {
        perror("Acceptor::setReuseAddr");
        return;
    }
}

void Acceptor::setReusePort()
{
    int on = 1;
    int ret = setsockopt(_socket.getFd(),SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));
    if(ret == -1)
    {
        perror("Acceptor::setReusePort");
        return;
    }
}

void Acceptor::bind()
{
    int ret = ::bind(_socket.getFd(),(struct sockaddr *)_addr.getInetAddressPtr(),sizeof(struct sockaddr));
    if(ret == -1)
    {
        perror("Acceptor::bind");
        return;
    }
}

void Acceptor::listen()
{
    int ret = ::listen(_socket.getFd(),128);
    if(ret == -1)
    {
        perror("Acceptor::listen");
        return;
    }
}

int Acceptor::accept()
{
    int connfd = ::accept(_socket.getFd(),nullptr,nullptr);
    if(connfd == -1)
    {
        perror("Acceptor::accept");
        return -1;
    }

    return connfd;
}

int Acceptor::getFd() const
{
    return _socket.getFd();
}