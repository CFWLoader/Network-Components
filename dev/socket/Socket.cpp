#include "Socket.h"

Clown::Socket::Socket()
{
	socketFileDescriptor = 0;
}

int Clown::Socket::getSocketFileDescriptor() const
{
	return socketFileDescriptor;
}
