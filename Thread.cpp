#include "Thread.h"
#include <iostream>

using namespace soran;

struct ThreadAgent
{
    typedef std::function<void()> ThreadFunction;

    ThreadFunction func_;

    ThreadAgent(const ThreadFunction& func) : func_(func){}

    void start()
    {
        func_();
    }

};

void* startThread(void* intermediateArgs)
{
    ThreadAgent* agent = static_cast<ThreadAgent*>(intermediateArgs);

    agent->start();

    delete agent;

    return nullptr;
}

Thread::Thread(std::function<void()> task) :
	task_(task)
{}

int Thread::start()
{
	ThreadAgent* agent = new ThreadAgent(task_);

	int retVal = pthread_create(&threadId_, nullptr, startThread, agent);

	if(retVal != 0)
	{
		delete agent;
	}

	return retVal;
}

int Thread::join()
{
	return 0;
}

int Thread::detach()
{
	return 0;
}
