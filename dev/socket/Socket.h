#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>

namespace Clown
{	
	class Socket{
		public:
			Socket();
			int getSocketFileDescriptor() const;
		private:
			int socketFileDescriptor;
	};
}

#endif
