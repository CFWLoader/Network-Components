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

		typedef std::function<void(void)> ThreadFunction;

		explicit Thread(int, TcpServer::CallBackOfServerCloseFD);

		void serveFunction();

		int start();

	private:
		TcpServer::CallBackOfServerCloseFD serverCallBack;

		int clientFD;

		pthread_t theThread;

	};
}

#endif