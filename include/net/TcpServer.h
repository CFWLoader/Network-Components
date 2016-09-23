#ifndef NET_TCPSERVER_H_
#define NET_TCPSERVER_H_

#include <nc/util/Atomic.h>
#include <nc/util/Types.h>
#include <nc/net/TcpConnection.h>

#include <map>
#include <memory>

namespace nc
{
	namespace net
	{
		class Acceptor;

		class EventLoop;

		class EventLoopThreadPool;

		class TcpServer : nc::util::Noncopyable
		{
		public:

			typedef std::function<void(EventLoop*)> ThreadInitCallback;

			enum Option
			{
				kNoReusePort,
				kResusePort,
			};

			TcpServer(EventLoop* loop,
				const InetAddress& listenAddr,
				const string& nameArg,
				Option option = kNoReusePort);

			~TcpServer();

			const string& ipPort() const
			{
				return ipPort_;
			}

			const string& name() const
			{
				return name_;
			}

			EventLoop* getLoop() const
			{
				return loop_;
			}

			void setThreadNum(int numThreads);

			void setThreadInitCallback(const ThreadInitCallback& cb)
			{
				threadInitCallback_ = cb;
			}

			std::shared_ptr<EventLoopThreadPool> threadPool()
			{
				return threadPool_;
			}

			void start();

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

		private:

			void newConnection(int sockfd, const InetAddres& peerAddr);

			void removeConnection(const TcpConnectionPtr& conn);

			void removeConnectionInLoop(const TcpConnectionPtr& conn);

			typedef std::map<string, TcpConnectionPtr> ConnectionMap;

			EventLoop* loop_;

			const string ipPort_;

			const string name_;

			std::scoped_ptr<Acceptor> acceptor_;

			std::shared_ptr<EventLoopThreadPool> threadPool_;

			ConnectionCallback connectionCallback_;

			MessageCallback messageCallback_;

			WriteCompleteCallback writeCompleteCallback_;

			ThreadInitCallback threadInitCallback_;

			AtomicInt32 started_;

			int nextConnId_;

			ConnectionMap connections_;
		};
	}
}

#endif