#include "ClownThread.h"

#include <unistd.h>
#include <cstdio>

#include <string>
#include <iostream>

void* clown::startThread(void* objPtr)
{
	clown::Thread* runningThread = static_cast<clown::Thread*>(objPtr);

	runningThread->serveFunction();

	return NULL;
}

clown::Thread::Thread(int socketFD, TcpServer::CallBackOfServerCloseFD callBack) : 
	serverCallBack(callBack),
	clientFD(socketFD)
{}

void clown::Thread::serveFunction()
{
	std::cout << "A thread opened for a client." << std::endl;

	char buffer[MAX_LINE];

	std::string echoMessage;

	int nRead = read(clientFD, buffer, MAX_LINE);

	if(nRead < 0)
	{
		fprintf(stderr, "A client happened exception, close this connection.\n");

		perror("Details: ");

		this->serverCallBack(clientFD);
	}
	else if(nRead == 0)
	{
		this->serverCallBack(clientFD);
	}
	else
	{
		buffer[nRead] = '\0';

		echoMessage.append(buffer);
		echoMessage.append("(From Server)\n");

        write(clientFD, echoMessage.c_str(), echoMessage.size());

        echoMessage.clear();
	}
}

int clown::Thread::start()
{
	::pthread_create(&theThread, 0, startThread, this);

	return 0;
}