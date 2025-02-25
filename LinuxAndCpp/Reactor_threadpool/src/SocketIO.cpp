#include "../include/SocketIO.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>


SocketIO::SocketIO(int fd)
:_fd(fd)
{

}

SocketIO::~SocketIO()
{
    close(_fd);
}

int SocketIO::readn(char * buf,int len)
{
    int left = len;
    char *p_str = buf;
    int ret = 0;

    while(left > 0)
    {
        ret = read(_fd,p_str,left);

        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("SocketIO::readn ret == -1");
            return -1;
        }
        else if (ret == 0)
        {
            break;
        }
        else
        {
            p_str += ret;
            left -= ret;
        }
    }
    return len - left;
}

int SocketIO::readLine(char * buf,int len)
{
    int left = len -1;
    char *p_str = buf;
    int ret = 0,total = 0;

    while(left>0)
    {
        //MSG_PEEK不会将缓冲区中的数据进行清空,只会进行拷贝操作
        ret = recv(_fd,p_str,left,MSG_PEEK);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("SocketIO::readLine ret == -1");
            return -1;
        }
        else if(ret == 0)
        {
            break;
        }
        else
        {
            for(int i = 0;i<ret;++i)
            {
                if(p_str[i] == '\n')
                {
                    int sz = i + 1;
                    readn(p_str,sz);
                    p_str += sz;
                    *p_str = '\0';//C风格字符串以'\0'结尾

                    return total+sz;
                }
            }

            readn(p_str,ret);//从内核态拷贝到用户态
            total += ret;
            p_str += ret;
            left -= ret;
        }
    }
    *p_str = '\0';

    return total -left;
}

int SocketIO::writen(const char *buf, int len)
{
    int left = len;
    const char *p_str = buf;
    int ret = 0;

    while(left > 0)
    {
        ret = write(_fd, p_str, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("SocketIO::writen ret == -1");
            return -1;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            p_str += ret;
            left -= ret;
        }
    }
    return len - left;
}