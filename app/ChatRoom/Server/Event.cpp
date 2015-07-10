#include "Event.h"
#include "ClownThread.h"

#include <functional>

#include <unistd.h>
#include <cassert>

#include <algorithm>

clown::Event::Event(const TcpServer::CallBackOfServerCloseFD& callBack, int socketFD) : 
	serverCallBack(callBack),
	clientFD(socketFD),
	finishedFlag(false)
{}

clown::Event::Event(const TcpServer::CallBackOfServerCloseFD& callBack, int socketFD, const std::function<void()>& echoCallBack) :
	serverCallBack(callBack),
	clientFD(socketFD),
	serverEchoCallBack(echoCallBack),
	finishedFlag(false)
{}

clown::Event::Event(int socketFD) :
	clientFD(socketFD),
	finishedFlag(false)
{}

clown::Event::Event(int socketFD, TcpServer* serverPtr) :
	clientFD(socketFD),
	serverPointer(serverPtr)
{}

void clown::Event::setCloseCallBack(const CloseCallBack& ccb)
{
	serverCallBack = ccb;
}

void clown::Event::serveFunction()
{
	//fprintf(stdout, "serveFunction.\n");

	char buffer[MAX_LINE];

	std::string echoMessage;

	int nRead = read(clientFD, buffer, MAX_LINE);

	if(nRead < 0)
	{
		fprintf(stderr, "A client happened exception, close this connection.\n");

		perror("Details: ");

		serverPointer->closeClientFD(clientFD);
	}
	else if(nRead == 0)
	{
		serverPointer->closeClientFD(clientFD);
	}
	else
	{
		//serverEchoCallBack();

		buffer[nRead] = '\0';

		echoMessage.append(buffer);
		echoMessage.append("(From Server)\n");

		echoMessage.erase(std::find(echoMessage.begin(), echoMessage.end(), '\n'));

        write(clientFD, echoMessage.c_str(), echoMessage.size());

        echoMessage.clear();
	}
}

int clown::Event::happen()
{
	clown::Thread::ThreadFunction registerFunction = std::bind(
		&clown::Event::serveFunction, this);

	clown::Thread eventThread(registerFunction);

	eventThread.start();

	finishedFlag = true;

	return 0;
}