#include "Event.h"
#include "ClownThread.h"

#include <functional>

#include <unistd.h>
#include <cassert>

#include <algorithm>

clown::Event::Event(int socketFD, const TcpServer::CallBackOfServerCloseFD& callBack) : 
	clientFD(socketFD),
	serverCallBack(callBack),
	finishedFlag(false)
{}

void clown::Event::serveFunction()
{

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

	finishedFlag = true;

	return 0;
}