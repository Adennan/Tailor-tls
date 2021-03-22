#include "epoll.h"
#include "crypto.h"

#define replay "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 23\r\nServer: Adennan\r\n\r\nWelcome to Adennan's Home"

using namespace tailor;
using namespace std;

EpollServer::EpollServer()
{
	this->listenSock = 0;
	this->epollfd = 0;
    this->maxCount = 0;
    this->events = NULL;
}
 
EpollServer::~EpollServer()
{
	if (this->listenSock > 0)
	{
		close(this->listenSock);
	}
    
	if (this->epollfd > 0)
	{
		close(this->epollfd);
	}
}
 
bool EpollServer::init(int port, int sockCount)
{
    this->maxCount = sockCount;	
	struct sockaddr_in server;
	memset(&server, 0, sizeof(&server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);		
 
	this->listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listenSock < 0)
	{
		perror("create socket error");
		exit(1);
	}
	
	cout << "Bind Local Port: " << port << endl;
	if (bind(this->listenSock, (struct sockaddr*)&server, sizeof(server)) == -1)
	{
		perror("bind socket error");
		exit(1);
	}

	setsockopt(this->listenSock, SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(opt));
	
	if (listen(this->listenSock, 5) == -1)
	{
		perror("listen socket error");
		exit(1);
	}
 
	this->events = new struct epoll_event[sockCount];
	if (this->events == NULL)
	{
		exit(1);
	}
 
	this->epollfd = epoll_create(sockCount);
    if (fcntl(this->epollfd, F_SETFL, fcntl(this->epollfd, F_GETFD, 0)|O_NONBLOCK) == -1) { 
        perror("fcntl(F_GETFL)\n"); 
        exit(1); 
    }

	struct epoll_event ev;
	ev.data.fd = this->listenSock;
	ev.events  = EPOLLIN;
	epoll_ctl(this->epollfd, EPOLL_CTL_ADD, this->listenSock, &ev);
}
 
bool EpollServer::init(const char* ip, int port , int sockCount)
{	
	int opt;
	this->maxCount = sockCount;
	struct sockaddr_in server;
	memset(&server, 0, sizeof(&server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ip);		
 
	this->listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listenSock < 0)
	{
		perror("create socket error");
		exit(1);
	}
	
	cout << "Bind Local Port: " << port << endl;
	if (bind(this->listenSock, (struct sockaddr*)&server, sizeof(server)) == -1)
	{
		perror("bind socket error");
		exit(1);
	}

	setsockopt(this->listenSock, SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(opt));
	
	if (listen(this->listenSock, 5) == -1)
	{
		perror("listen socket error");
		exit(1);
	}
 
	this->events = new struct epoll_event[sockCount];
	if (this->events == NULL)
	{
		exit(1);
	}
 
	this->epollfd = epoll_create(sockCount);
    if (fcntl(this->epollfd, F_SETFL, fcntl(this->epollfd, F_GETFD, 0)|O_NONBLOCK) == -1) { 
        perror("fcntl(F_GETFL)\n"); 
        exit(1); 
    }

	struct epoll_event ev;
	ev.data.fd = this->listenSock;
	ev.events  = EPOLLIN;
	epoll_ctl(this->epollfd, EPOLL_CTL_ADD, this->listenSock, &ev);
}

// 设置socket连接为非阻塞模式 
void EpollServer::setnonblocking(int sockfd) {
    if(fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) { 
        perror("fcntl(F_GETFL)\n"); 
        exit(1); 
    }
}
 
int EpollServer::acceptClient()
{
	sockaddr_in client;
	memset(&client, 0, sizeof(client));
    socklen_t clilen = sizeof(struct sockaddr); 
    int newSock = accept(this->listenSock, (struct sockaddr*)&client, &clilen);
	struct epoll_event ev;
	ev.data.fd = newSock;
	ev.events  = EPOLLIN;
	epoll_ctl(this->epollfd, EPOLL_CTL_ADD, newSock, &ev);

	// void handshake()
	return newSock;
}
 
int EpollServer::recvData(int sock, char* buffer)
{
	char buf[1024] = {0};
	int len = 0;
	int ret = 0;
	while (ret >= 0)
	{
		ret = recv(sock, buf, sizeof(buf), 0);
		if (ret <= 0)
		{
			struct epoll_event ev;
			ev.data.fd = sock;
			ev.events  = EPOLLERR;
			epoll_ctl(this->epollfd, EPOLL_CTL_DEL, sock, &ev);
			close(sock);
			break;
		}
		else if (ret < 1024)
		{
			memcpy(buffer, buf, ret);
			len += ret;	
			struct epoll_event ev;
			ev.data.fd = sock;
			ev.events  = EPOLLOUT;
			epoll_ctl(this->epollfd, EPOLL_CTL_MOD, sock, &ev);
			break;
		}
		else
		{
			memcpy(buffer, buf, sizeof(buf));
			len += ret;
		}
	}
    cout << buffer;

	return ret <= 0 ? ret : len;
}
 
int EpollServer::sendData(int sock, char* buffer, int bufLen)
{
	int len = 0;
	int ret = 0;
	while(len < bufLen)
	{
		ret = send(sock, buffer + len, 1024, 0);
		if(ret <= 0)
		{
			struct epoll_event ev;
			ev.data.fd = sock;
			ev.events  = EPOLLERR;
			epoll_ctl(this->epollfd, EPOLL_CTL_DEL, sock, &ev);
			close(sock);
			break;
		}
		else
		{
			len += ret;
		}
 
		if(ret < 1024)
		{
			break;
		}
	}
 
	if(ret > 0)
	{
		struct epoll_event ev;
		ev.data.fd = sock;
		ev.events  = EPOLLIN;
		epoll_ctl(this->epollfd, EPOLL_CTL_MOD, sock, &ev);
	}
 
	return ret <= 0 ? ret : len;
}
 
int EpollServer::epollWait(int timeout)
{
	int fds = epoll_wait(this->epollfd, this->events, this->maxCount, timeout);
    return fds;
}
 
void EpollServer::run(int timeout)
{
	struct timeval times = {3, 0};
	char *recvBuf = new char[65535];
	char *sendBuf = new char[65535];

	// tailor-tls init


	while (1)
	{
		int ret = epollWait(timeout);
		if (ret == 0)
		{
			cout << "Waiting Client Connection..." << endl;
			continue;
		}
		else if (ret == -1)
		{
			cout << "error" << endl;
		}
		else
		{
			for (int i = 0; i < ret; i++)
			{
				if (this->events[i].data.fd == this->listenSock)
				{
					if (this->events[i].events & EPOLLIN)
					{
						int clientfd = acceptClient();
						if (clientfd < 0)
						{
							close(this->listenSock);
							cout << "Accept Error" << endl;
							exit(-2);
						}
						cout << "Loading new client: " << clientfd << endl;
						envInit();

						setsockopt(clientfd, SOL_SOCKET, SO_RCVTIMEO, &times, sizeof(times));

						if (handshake(clientfd) != 0)
						{
							cout << "handshake error" << endl;
							close(clientfd);
						}

						memset(recvBuf, 0 ,sizeof(recvBuf));
						cout << "Try to read " << sizeof(recvBuf) << " bytes from client.....\n" << endl;
						ret = recvData(clientfd, recvBuf);
						if (ret <= 0) {
							cout << "ret:%d\n" << ret << endl;
							if (ret == -6) {
								cout << "Read fin" << endl;
							} else {
								cout << "Read error" << endl;
							}
							close(clientfd);
						}
						cout << "Recv " << ret << " bytes from client " << recvBuf << endl;
						ret = sendData(clientfd, (unsigned char*)replay, sizeof(replay));
						cout << "reply to client: " << ret << endl;

						if (this->listenSock) {
							close(this->listenSock);
						}
					}
				}
				// else
				// {
				// 	if (this->events[i].events & EPOLLIN)
				// 	{
				// 		int recvCount = recvData(this->events[i].data.fd, recvBuf);
				// 		cout << "【size】 " << recvCount << "【data】 " << recvBuf << endl;
				// 		strcpy(sendBuf, recvBuf);
				// 		memset(recvBuf, 0, sizeof(recvBuf));
				// 	}
				// 	else if (this->events[i].events & EPOLLOUT)
				// 	{
				// 		int sendCount = sendData(this->events[i].data.fd, sendBuf, strlen(sendBuf));
				// 		memset(sendBuf, 0, sizeof(sendBuf));
				// 	}
					
				// }
			}
		}
	}
}