#include <iostream>

#include <unistd.h>

#include <util/Thread.h>
#include <util/ThreadPool.h>

using namespace soran::util;

ThreadPool::ThreadPool(unsigned int poolSize) : 
	threads_(poolSize),
	shutdownSignal_(false)
{
	bool& sdSig(shutdownSignal_);

	for(unsigned int idx = 0; idx < poolSize; ++idx)
	{
		threads_[idx] = new Thread([&sdSig]()
			{
				while(!sdSig)
				{
					std::cout << "Thread " << pthread_self() << " is working." << std::endl;

					sleep(1);
				}
			});

		threads_[idx]->start();
	}

	for(unsigned int idx = 0; idx < poolSize; ++idx)
	{
		threads_[idx]->join();
	}
}

ThreadPool::~ThreadPool()
{
	for(unsigned int idx = 0; idx < threads_.size(); ++idx)
	{
		delete threads_[idx];
	}
}