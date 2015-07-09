#include "TcpServer.h"

#include <functional>
#include <iostream>

#include <cstdio>

using namespace clown;
using namespace std;

int main(int argc, char* argv[])
{
	
	TcpServer server;

	//pid_t theMainThreadID = static_cast<pid_t>(::syscall(SYS_gettid));

	//cout << "Main Thread ID: " << static_cast<unsigned long>(theMainThreadID) << end;

	//printf("Main Thread ID: %ld\n", theMainThreadID);

	//theThread.join();
	//cbc.busy();

	server.initialize();

	server.serve();

	return 0;
}