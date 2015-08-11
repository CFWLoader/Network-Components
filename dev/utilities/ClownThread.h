#ifndef CLOWNTHREAD_H_
#define CLOWNTHREAD_H_

#include <functional>

#include "TcpServer.h"

#include <pthread.h>

#define MAX_LINE 2048

namespace clown
{
	void* startThread(void*);

	class Thread{
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