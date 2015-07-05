#ifndef TCPSERVER_H_
#define TCPSERVER_H_

extern unsigned short SERVER_PORT;

namespace clown
{
	class TcpServer
	{
	public:

		TcpServer();

		int initialize();

		int serve();

		~TcpServer();

	private:

		int socketFileDescriptor;
	};
}

#endif