#ifndef CLOWNEVENT_H_
#define CLOWNEVENT_H_

#include "TcpServer.h"

namespace clown
{
	class Event{
	public:

		typedef TcpServer::CallBackOfServerCloseFD CloseCallBack;

		explicit Event(const TcpServer::CallBackOfServerCloseFD&, int);

		explicit Event(const TcpServer::CallBackOfServerCloseFD&, int, const std::function<void()>&);

		explicit Event(int);

		explicit Event(int, TcpServer*);

		void setCloseCallBack(const CloseCallBack&);

		void serveFunction();

		int happen();

		inline bool isFinished() const;

	private:
		CloseCallBack serverCallBack;

		int clientFD;

		std::function<void()> serverEchoCallBack;

		bool finishedFlag;

		TcpServer* serverPointer;
	};
}

inline bool clown::Event::isFinished() const
{
	return finishedFlag;
}

#endif