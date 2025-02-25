#include "../include/Socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

Socket::Socket()
{
    _fd = ::socket(AF_INET,SOCK_STREAM,0);
    if(_fd<0)
    {
        perror("Socket::Socket()");
        return;
    }
}

Socket::Socket(int fd)
:_fd(fd)
{

}

Socket::~Socket()
{
    close(_fd);
}

int Socket::getFd() const
{
    return _fd;
}

void Socket::shutdownWrite()
{
    int ret = shutdown(_fd,SHUT_WR);
    if(ret)
    {
        perror("Socket::shutdownWrite");
        return;
    }
}