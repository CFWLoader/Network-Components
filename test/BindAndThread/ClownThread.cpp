#include "ClownThread.h"

#include <unistd.h>
#include <cstdio>

#include <string>
#include <iostream>

namespace clown
{
	struct ThreadData
	{
		typedef clown::Thread::ThreadFunction ThreadFunction;

		ThreadFunction threadFunction;

		explicit ThreadData(const ThreadFunction&);

		int _start();
	};
}

clown::ThreadData::ThreadData(const ThreadFunction& registeringFunction) : threadFunction(registeringFunction)
{}

int clown::ThreadData::_start()
{
	threadFunction();

	return 0;
}

void* clown::startThread(void* objPtr)
{
	clown::ThreadData* runningThread = static_cast<clown::ThreadData*>(objPtr);

	runningThread->_start();

	//std::cout << "In thread: " << runningThread->getTheServerInstance() << std::endl;

	//runningThread->closeConnection();
	delete runningThread;

	return NULL;
}

clown::Thread::Thread(const ThreadFunction& registerFunction) : threadFunction(registerFunction)
{}

/*
clown::Thread::Thread(const TcpServer::CallBackOfServerCloseFD& callBack, int socketFD) : 
	serverCallBack(callBack),
	clientFD(socketFD)
{}

clown::Thread::Thread(const TcpServer::CallBackOfServerCloseFD& callBack, int socketFD, const std::function<void()>& echoCallBack) :
	serverCallBack(callBack),
	clientFD(socketFD),
	serverEchoCallBack(echoCallBack)
{}
*/

/*
clown::Thread::Thread(int socketFD, clown::TcpServer* theServer) : clientFD(socketFD),
	theServerHandler(theServer)
{
	//std::cout << "In thread constructor: " << theServerHandler << std::endl;
}
*/

/*
void clown::Thread::serveFunction()
{
	char buffer[MAX_LINE];

	std::string echoMessage;

	int nRead = read(clientFD, buffer, MAX_LINE);

	if(nRead < 0)
	{
		fprintf(stderr, "A client happened exception, close this connection.\n");

		perror("Details: ");

		serverCallBack();
		//::close(clientFD);
		//theServerHandler->closeClientFD(clientFD);
	}
	else if(nRead == 0)
	{
		//fprintf(stdout, "Client Thread: A connection closed.\n");

		serverCallBack();
		//::close(clientFD);
		//theServerHandler->closeClientFD(clientFD);

		//fprintf(stdout, "Client Thread: A connection closed via callBack.\n");
	}
	else
	{
		//std::cout << "A invoking TcpServer::echoFromThread()." << std::endl;

		serverEchoCallBack();

		buffer[nRead] = '\0';

		echoMessage.append(buffer);
		echoMessage.append("(From Server)\n");

        write(clientFD, echoMessage.c_str(), echoMessage.size());

        echoMessage.clear();
	}
}
*/

int clown::Thread::start()
{
	ThreadData* runningInstance = new ThreadData(threadFunction);

	if(::pthread_create(&theThread, 0, &startThread, runningInstance))
	{
		delete runningInstance;
	}

	return 0;
}

int clown::Thread::run()
{
	threadFunction();

	return 0;
}

int clown::Thread::join()
{
	return ::pthread_join(theThread, 0);	
}