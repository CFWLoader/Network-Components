#include <iostream>

// #include "../Socket.h"
// #include "../Socket.cpp"
#include <Socket.h>

using namespace std;

int testCase1();

int main(int argc, char* argv[])
{
	testCase1();

	return 0;
}

int testCase1()
{
	clown::Socket socket;

	cout << socket.getSocketFileDescriptor() << endl;

	cout << "Hello world!" << endl;

	return 0;
}