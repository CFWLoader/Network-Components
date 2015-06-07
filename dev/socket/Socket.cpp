#include "Socket.h"

clown::Socket::Socket()
{
	socketFileDescriptor = 0;
}

int clown::Socket::getSocketFileDescriptor() const
{
	return socketFileDescriptor;
}
