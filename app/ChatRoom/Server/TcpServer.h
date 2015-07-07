#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <netinet/in.h>
#include <arpa/inet.h>

#include <functional>

extern unsigned short SERVER_PORT;

extern size_t MAX_LISTEN_QUEUE;

extern size_t MAX_CLIENT_NUMBER;

namespace clown
{
	class TcpServer
	{
	public:
		typedef std::function<int(int)> CallBackOfServerCloseFD;

		TcpServer();

		int initialize();

		int serve();

		int setNonBlocking(int);

		int closeClientFD(int);

		~TcpServer();

	private:
		int socketFileDescriptor;

		sockaddr_in serverAddress;
	};
}

#endif