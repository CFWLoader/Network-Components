#include "TcpServer.h"

int main(int argc, char* argv[])
{
	clown::TcpServer theServer;

	theServer.initialize();

	theServer.serve();

	return 0;
}