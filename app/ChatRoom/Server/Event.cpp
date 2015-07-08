#include "Event.h"
#include "ClownThread.h"

#include <functional>

#include <unistd.h>
#include <cassert>

clown::Event::Event(const TcpServer::CallBackOfServerCloseFD& callBack, int socketFD) : 
	serverCallBack(callBack),
	clientFD(socketFD)
{}

clown::Event::Event(const TcpServer::CallBackOfServerCloseFD& callBack, int socketFD, const std::function<void()>& echoCallBack) :
	serverCallBack(callBack),
	clientFD(socketFD),
	serverEchoCallBack(echoCallBack)
{}

clown::Event::Event(int socketFD) :
	clientFD(socketFD)
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

		serverCallBack();
	}
	else if(nRead == 0)
	{
		serverCallBack();
	}
	else
	{
		//serverEchoCallBack();

		buffer[nRead] = '\0';

		echoMessage.append(buffer);
		echoMessage.append("(From Server)\n");

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

	return 0;
}