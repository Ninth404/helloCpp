#ifndef __SOCKET_H__
#define __SOCKET_H__

class Socket
{
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();
    int getFd() const;
    void shutdownWrite();

    Socket(const Socket & rhs) = delete;
    Socket(const Socket && rhs) = delete;
    Socket & operator=(const Socket & rhs) = delete;
    Socket & operator=(const Socket && rhs) = delete;

private:
    int _fd;
};

#endif