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

	delete runningThread;

	return NULL;
}

clown::Thread::Thread(const ThreadFunction& registerFunction) : threadFunction(registerFunction)
{}

clown::Thread::Thread(int fd, const CloseHandler& cb) : 
	targetFD(fd),
	closeHandler(cb)
{}

int clown::Thread::start()
{
	threadFunction = std::bind(&Thread::serverFunction, this);

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

void clown::Thread::serverFunction()
{
	char buffer[MAX_LINE];

	std::string echoMessage;

	int nRead = read(targetFD, buffer, MAX_LINE);

	if(nRead < 0)
	{
		fprintf(stderr, "A client happened exception, close this connection.\n");

		perror("Details: ");

		closeHandler();
	}
	else if(nRead == 0)
	{
		closeHandler();
	}
	else
	{
		buffer[nRead] = '\0';

		echoMessage.append(buffer);
		echoMessage.append("(From Server)\n");

        write(targetFD, echoMessage.c_str(), echoMessage.size());

        echoMessage.clear();
	}
}