#ifndef EPOLL_H
#define EPOLL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>

using namespace std;

namespace tailor {
    class EpollServer {
    private:
        int listenSock;
        int epollfd;
        int maxCount;
        struct epoll_event *events;
    
    public:
        EpollServer();
        virtual ~EpollServer();
        bool init(int port, int sockCount);
        bool init(const char* ip, int port, int sockCount);
        void setnonblocking(int sockfd);
        int epollWait(int timeout);
        int acceptClient();
        int recvData(int sock, char* buffer);
        int sendData(int sock, char* buffer, int len);
        void run(int timeout);
    };
}

#endif // EPOLL_H