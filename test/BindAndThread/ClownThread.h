#ifndef CLOWNTHREAD_H_
#define CLOWNTHREAD_H_

#include <functional>

#include <pthread.h>

#include "TcpServer.h"

#define MAX_LINE 2048

namespace clown
{
	void* startThread(void*);

	class Thread{
	public:
		typedef std::function<void()> ThreadFunction;

		typedef TcpServer::CallBackOfServerCloseFD CloseHandler;

		explicit Thread(const ThreadFunction&);

		explicit Thread(int, const CloseHandler&);

		int start();

		int run();

		int join();

		void serverFunction();

	private:

		ThreadFunction threadFunction;

		pthread_t theThread;

		int targetFD;

		CloseHandler closeHandler;

		//TcpServer* theServerHandler;
	};
}

/*
inline clown::TcpServer* clown::Thread::getTheServerInstance() const
{
	return theServerHandler;
}
*/

#endif