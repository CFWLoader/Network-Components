#ifndef NET_TCPCLIENT_H_
#define NET_TCPCLIENT_H_

#include <nc/util/Noncopable.hpp>
#include <nc/util/Mutex.h>
#include <nc/net/TcpConnection.h>

namespace nc
{
	namespace net
	{
		class Connector;

		typedef std::shared_ptr<Connector> ConnectorPtr;

		class TcpClient : nc::util::Noncopable
		{
		public:

			TcpClient(EventLoop* loop,
				const InetAddress& serverAddr,
				const string& nameArg);

			~TcpClient();

			void connect();

			void disconnect();

			void stop();

			TcpConnectionPtr connection() const
			{
				MutexLockGuard lock(mutex_);

				return connection_;
			}

			EventLoop* getLoop() const
			{
				return loop_;
			}

			bool retry() const
			{
				return retry_;
			}

			void enableRetry()
			{
				retry_ = true;
			}

			const string& name() const
			{
				return name_;
			}

			void setConnectionCallback(const ConnectionCallback& cb)
			{
				connectionCallback_ = cb;
			}

			void setMessageCallback(const MessageCallback& cb)
			{
				messageCallback_ = cb;
			}

			void setWriteCompleteCallback(const WriteCompleteCallback& cb)
			{
				writeCompleteCallback_ = cb;
			}

			void setConnectionCallback(ConnectionCallback&& cb)
			{
				connectionCallback_ = std::move(cb);
			}

			void setMessageCallback(MessageCallback&& cb)
			{
				messageCallback_ = std::move(cb);
			}

			void setWriteCompleteCallback(WriteCompleteCallback&& cb)
			{
				writeCompleteCallback_ = std::move(cb);
			}

		private:

			void netConnection(int sockfd);

			void removeConnection(const TcpConnectionPtr& conn);

			EventLoop* loop_;

			ConnectorPtr connector_;

			const string name_;

			ConnectionCallback connectionCallback_;

			MessageCallback messageCallback_;

			WriteCompleteCallback writeCompleteCallback_;

			bool retry_;

			bool connect_;

			int nextConnId_;

			mutable MutexLock mutex_;

			TcpConnectionPtr connection_;
		};
	}
}

#endif