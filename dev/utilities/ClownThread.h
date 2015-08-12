#ifndef CLOWNTHREAD_H_
#define CLOWNTHREAD_H_

#include <functional>

#include "Noncopyable.hpp"

#include <pthread.h>

#define MAX_LINE 2048

namespace clown
{
	void* startThread(void*);

	class Thread : public utilities::Noncopyable{
	public:

		typedef std::function<void()> ThreadFunction;

		explicit Thread(const ThreadFunction&);

		int start();

	private:

		ThreadFunction threadFunction;

		pthread_t theThread;

	};
}


#endif