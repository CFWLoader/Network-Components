#ifndef CLOWNEVENT_H_
#define CLOWNEVENT_H_

#include "TcpServer.h"

namespace clown
{
	class Event{
	public:

		typedef TcpServer::CallBackOfServerCloseFD CloseCallBack;

		explicit Event(int, const TcpServer::CallBackOfServerCloseFD&);

		void serveFunction();

		int happen();

		inline bool isFinished() const;

	private:

		int clientFD;

		CloseCallBack serverCallBack;

		bool finishedFlag;
	};
}

inline bool clown::Event::isFinished() const
{
	return finishedFlag;
}

#endif