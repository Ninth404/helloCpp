#ifndef __INET_ADDRESS_H__
#define __INET_ADDRESS_H__

#include <arpa/inet.h>
#include <string>

using std::string;

class InetAddress
{
public:
    InetAddress(const string & ip,unsigned short port);

    InetAddress(const struct sockaddr_in & addr);

    ~InetAddress();

    string getIp() const;

    unsigned short getPort() const;

    const struct sockaddr_in * getInetAddressPtr() const;

private:
    struct sockaddr_in _addr;
};

#endif