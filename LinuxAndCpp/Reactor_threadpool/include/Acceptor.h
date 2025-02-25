#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "../include/Socket.h"
#include "../include/InetAddress.h"

class Acceptor
{
public:
    Acceptor(const string & ip,unsigned short port);
    ~Acceptor();
    void ready();
    int accept();
    int getFd() const;
private:
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();
private:
    Socket _socket;
    InetAddress _addr;    
};

#endif