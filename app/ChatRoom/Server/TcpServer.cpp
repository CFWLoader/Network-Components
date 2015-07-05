#include "Server.h"

#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

clown::TcpServer::TcpServer() : socketFileDescriptor(-1)
{}

clown::TcpServer::~TcpServer()
{
	close(socketFileDescriptor);
}

int clown::TcpServer::initilize()
{
	socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

	if(socketFileDescriptor == -1)
	{
		fprintf(stderr, "Error: socket()\n");

		perror();

		return -1;
	}
}