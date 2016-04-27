#include <iostream>

#include <Socket.h>

clown::Socket::Socket()
{
	socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

	if(socketFileDescriptor < 0){
		std::cerr << "Error in getting socket." << std::endl;
	}
}

int clown::Socket::getSocketFileDescriptor() const
{
	return socketFileDescriptor;
}
