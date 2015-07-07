#ifndef CLOWNEVENT_H_
#define CLOWNEVENT_H_

#include "TcpServer.h"

namespace clown
{
	class Event{
	public:

		explicit Event(const TcpServer::CallBackOfServerCloseFD&, int);

		explicit Event(const TcpServer::CallBackOfServerCloseFD&, int, const std::function<void()>&);

		void serveFunction();

		int happen();

	private:
		TcpServer::CallBackOfServerCloseFD serverCallBack;

		int clientFD;

		std::function<void()> serverEchoCallBack;
	};
}

#endif