#include <unistd.h>
#include <cstdio>

#include <string>
#include <iostream>

#include <Thread.h>

namespace nc
{
	namespace util
	{
		struct ThreadData
		{
			typedef Thread::ThreadFunction ThreadFunction;

			ThreadFunction threadFunction;

			explicit ThreadData(const ThreadFunction&);

			int _start();
		};
	}
}

nc::util::ThreadData::ThreadData(const ThreadFunction& registeringFunction) : threadFunction(registeringFunction)
{}

int nc::util::ThreadData::_start()
{
	threadFunction();

	return 0;
}

void* nc::util::startThread(void* objPtr)
{
	nc::util::ThreadData* runningThread = static_cast<nc::util::ThreadData*>(objPtr);

	runningThread->_start();

	delete runningThread;

	return NULL;
}

nc::util::Thread::Thread(const ThreadFunction& registerFunction) : threadFunction(registerFunction)
{}

int nc::util::Thread::start()
{
	ThreadData* runningInstance = new ThreadData(threadFunction);

	if(::pthread_create(&theThread, 0, &startThread, runningInstance))
	{
		delete runningInstance;
	}

	return 0;
}


void nc::util::Thread::setRunningFlag(bool flagValue)
{
	isRunning = flagValue;
}

bool nc::util::Thread::getRunningFlag() const
{
	return isRunning;
}