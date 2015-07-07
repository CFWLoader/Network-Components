#include "TcpServer.h"
#include "Event.h"

//POSIX
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>

//C Standard
#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include <cstring>

//C++
#include <vector>
#include <string>
#include <iostream>

unsigned short SERVER_PORT = 4433;

size_t MAX_LISTEN_QUEUE = 128;

size_t MAX_CLIENT_NUMBER = 256;

clown::TcpServer::TcpServer() : socketFileDescriptor(-1)
{
	bzero(&serverAddress, sizeof(serverAddress));
}

clown::TcpServer::~TcpServer()
{
	close(socketFileDescriptor);
}

int clown::TcpServer::initialize()
{
	socklen_t socketLength = sizeof(sockaddr);

	socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

	if(socketFileDescriptor == -1)
	{
		fprintf(stderr, "Error: socket()\n");

		perror("Detail: ");

		return -1;
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(SERVER_PORT);

	int result = bind(socketFileDescriptor, (sockaddr*)&serverAddress, socketLength);

	if(result == -1)
	{
		fprintf(stderr, "Error: bind()\n");

		perror("Detail: ");

		close(socketFileDescriptor);

		return -2;
	}

	result = listen(socketFileDescriptor, MAX_LISTEN_QUEUE);

	if(result == -1)
	{
		fprintf(stderr, "Error: listen()\n");

		perror("Detail: ");

		close(socketFileDescriptor);

		return -2;
	}

	return 0;
}

int clown::TcpServer::serve()
{
	int connectFD, epollFD;								//File Descriptors.

	int result, nReady, i;

	//int nRead;

	//char buffer[MAX_LINE];

	std::string echoMessage;

	sockaddr_in clientAddress;

	socklen_t clientLength = sizeof(sockaddr);

	epollFD = epoll_create(MAX_CLIENT_NUMBER);

	if(epollFD == -1)
	{
		fprintf(stderr, "Error: epoll_create()\n");

		perror("Details: ");

		return -1;
	}

	epoll_event settingEvent;

	std::vector<epoll_event> clientEvents(MAX_CLIENT_NUMBER);

	settingEvent.events = EPOLLIN;

	settingEvent.data.fd = socketFileDescriptor;

	result = epoll_ctl(epollFD, EPOLL_CTL_ADD, socketFileDescriptor, &settingEvent);

	if(result == -1)
	{
		fprintf(stderr, "Error: epoll_ctl()\n");

		perror("Details: ");

		close(epollFD);

		return -2;
	}

	while(true)
	{
		nReady = epoll_wait(epollFD, clientEvents.data(), MAX_CLIENT_NUMBER, -1);

		if(nReady == -1)
		{
			fprintf(stderr, "Error: epoll_wait()\n");

			perror("Details: ");

			close(epollFD);

			return -3;
		}

		for(i = 0; i < nReady; ++i)
		{
			if(clientEvents[i].data.fd == socketFileDescriptor)
			{
				connectFD = accept(socketFileDescriptor, (sockaddr*)(&clientAddress), &clientLength);

				if(connectFD == -1)
				{
					perror("A failed client connection, ignored.\n");

					continue;
				}

				this->setNonBlocking(connectFD);

				settingEvent.events = EPOLLIN | EPOLLET;
				settingEvent.data.fd = connectFD;

				result = epoll_ctl(epollFD, EPOLL_CTL_ADD, connectFD, &settingEvent);

				if(result == -1)
				{
					fprintf(stderr, "Error: epoll_ctl() for client, ignored.\n");

					perror("Details: ");

					continue;
				}

			}
			else
			{
				clown::Event clientEventThread(
					std::bind(&TcpServer::closeClientFD, this, static_cast<int>(clientEvents[i].data.fd)),
					clientEvents[i].data.fd,
					std::bind(&TcpServer::echoFromThread, this)
					);

				clientEventThread.happen();
				//std::cout << "Server: A thread is starting for a client." << std::endl;
				/*
				clown::Thread clientThread(std::bind(&clown::TcpServer::closeClientFD, this, static_cast<int>(clientEvents[i].data.fd)),
					clientEvents[i].data.fd);
					*/
				/*
				clown::Thread clientThread(
					std::bind(&TcpServer::closeClientFD, this, static_cast<int>(clientEvents[i].data.fd)),
					clientEvents[i].data.fd,
					std::bind(&TcpServer::echoFromThread, this)
					);
					*/
				/*
				clown::Thread clientThread(clientEvents[i].data.fd, this);

				std::cout << "Server instance address: " << this << std::endl;				
				*/

				//clientThread.start();
				//clientThread.serveFunction();
				/*
				nRead = read(clientEvents[i].data.fd, buffer, MAX_LINE);

				if(nRead < 0)
				{
					fprintf(stderr, "A client happened exception, close this connection.\n");

					perror("Details: ");

					close(clientEvents[i].data.fd);
				}
				else if(nRead == 0)
				{
					close(clientEvents[i].data.fd);
				}
				else
				{
					buffer[nRead] = '\0';

					echoMessage.append(buffer);
					echoMessage.append("(From Server)\n");

                    write(clientEvents[i].data.fd, echoMessage.c_str(), echoMessage.size());

                    echoMessage.clear();
				}
				*/
			}
		}
	}

	return 0;
}

int clown::TcpServer::setNonBlocking(int sockfd)
{
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}

int clown::TcpServer::closeClientFD(int fd)
{
	return ::close(fd);
}

void clown::TcpServer::echoFromThread()
{
	std::cout << "The function is invoked by other thread." << std::endl;
}