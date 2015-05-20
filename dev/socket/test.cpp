#include <iostream>

#include "Socket.h"

using namespace std;

int main(int argc, char* argv[])
{
	Clown::Socket socket;

	cout << socket.getSocketFileDescriptor() << endl;

	cout << "Hello world!" << endl;
	return 0;
}
