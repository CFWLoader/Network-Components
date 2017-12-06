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

				std::cout << "Thread " << pthread_self() << " received SIG_SHUTDOWN." << std::endl;				
			});

		threads_[idx]->start();
	}

	// for(unsigned int idx = 0; idx < poolSize; ++idx)
	// {
	// 	threads_[idx]->join();
	// }

	// std::cout << "Thread " << pthread_self() << " joined all." << std::endl;
}

ThreadPool::~ThreadPool()
{
	for(unsigned int idx = 0; idx < threads_.size(); ++idx)
	{
		delete threads_[idx];
	}
}

int ThreadPool::shutdownAll()
{
	shutdownSignal_ = true;	

	return 0;
}

int ThreadPool::joinAll()
{
	for(unsigned int idx = 0; idx < threads_.size(); ++idx)
	{
		threads_[idx]->join();
	}

	std::cout << "Thread " << pthread_self() << " joined all." << std::endl;

	return 0;
}