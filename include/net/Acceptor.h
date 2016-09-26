#ifndef NET_ACCEPTOR_H_
#define NET_ACCEPTOR_H_

#include <functional>

#include <nc/util/Noncopyable.hpp>
#include <nc/net/Channel.h>
#include <nc/net/Socket.h>

namespace nc
{
	namespace net
	{
		class EventLoop;

		class InetAddress;

		class Acceptor : nc::util::Noncopyable
		{
		public:
			typedef std::function<void(int sockfd, const InetAddress&)> NewConnectionCallback;

			Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport);

			~Acceptor();

			void setNewConnectionCallback(const NewConnectionCallback& cb)
			{
				newConnectionCallback_ = cb;
			}

			bool listening() const
			{
				return listening_;
			}

			void listen();

		private:

			void handleRead();

			EventLoop* loop_;	

			Socket acceptSocket_;

			Channel accpetChannel_;

			NewConnectionCallback newConnectionCallback_;

			bool listening_;

			int idleFd_;

		};
	}
}

#endif
