#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "Noncopyable.hpp"

namespace clown
{
	class Thread;

	class ThreadPool : public utilities::Noncopyable
	{
	public:
	private:
		
		Thread* threads;

		int numberOfThread;
	};
}

#endif
