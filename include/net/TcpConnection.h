#ifndef NET_TCPCONNECTION_H_
#define NET_TCPCONNECTION_H_

#include <nc/util/StringPiece.h>
#include <nc/util/Types.h>
#include <nc/util/Noncopyable.hpp>
#include <nc/net/Callbacks.h>
#include <nc/net/Buffer.h>
#include <nc/net/InetAddress.h>

#include <memory>

struct tcp_info;

namespace nc
{
	namespace net
	{
		class Channel;

		class EventLoop;

		class Socket;

		class TcpConnection : nc::util::Noncopyable, public boost::enable_shared_from_this<TcpConnection>
		{
		public:

			TcpConnection(EventLoop* loop,
				const string& name,
				int sockfd,
				const InetAddress& localAddr,
				const InetAddress& peerAddr);

			~TcpConnection();

			EventLoop* getLoop() const
			{
				return loop_;
			}

			const string& name() const
			{
				return name_;
			}

			const InetAddress& localAddress() const
			{
				return localAddr_;
			}

			const InetAddress& peerAddr() const
			{
				return peerAddr_;
			}

			bool connected() const
			{
				return state_ == kConnected;
			}

			bool disconnected() const
			{
				return state_ == kDisconnected;
			}

			bool getTcpInfo(struct tcp_info*) const;

			string getTcpInfoString() const;

			void send(string&& message);

			void send(const void* message, int len);

			void send(const StringPiece& message);

			void send(Buffer&& message);

			void send(Buffer* message);

			void shutdown();

			void forceClose();

			void forceCloseWithDelay(double seconds);

			void setTcpNoDelay(bool on);

			void startRead();

			void stopRead();

			bool isReading() const
			{
				return reading_;
			}

			void setContext(const boost::any& context)
			{
				context_ = context;
			}

			const boost::any& getContext() const
			{
				return &context_;
			}

			void setConnectionCallback(const ConnectionCallback& cb)
			{
				connectionCallback_ = cb;
			}

			void setMessageCallback(const MessageCallback& cb)
			{
				messageCallbck_ = cb;
			}

			void setWriteCompleteCallback(const WriteCompleteCallback& cb)
			{
				writeCompleteCallback = cb;
			}

			void setHighWaterMarkCallback(const HighWatermarkCallback& cb, size_t highWaterMark)
			{
				highWaterMarkCallback_ = cb;

				highWaterMark_ = highWaterMark;
			}

			Buffer* inputBuffer()
			{
				return &inputBuffer_;
			}

			Buffer* outputBuffer()
			{
				return &outputBuffer_;
			}

			void setCloseCallback(const CloseCallback& cb)
			{
				closeCallback_ = cb;
			}

			void connectEstablished();

			void connectDestroyed();

		private:

			enum StateE{kDisconnected, kConnecting, kConnected, kDisconnected};

			void handleRead(Timestamp& receiveTime);

			void handleWrite();

			void handleClose();

			void handleError();

			void sendInLoop(string&& message);

			void sendInLoop(const StringPiece& message);

			void sendInLoop(const void* message, size_t len);

			//void shutdownAndForceCloseInLoop(double seconds);

			void forceCloseInLoop();

			void setState(StateE s)
			{
				state_ = s;
			}

			const char* stateToString() const;

			void startReadInLoop();

			void stopReadInLoop();

			EventLoop* loop_;

			const string name_;

			StateE state_;

			std::scoped_ptr<Socket> socket_;

			std::scoped_ptr<Channel> channel_;

			const InetAddress localAddr_;

			const InetAddress peerAddr_;

			ConnectionCallback connectionCallback_;

			MessageCallback messageCallback_;

			WriteCompleteCallback writeCompleteCallback_;

			HighWatermarkCallback highWaterMarkCallback_;

			CloseCallback closeCallback_;

			size_t highWaterMark_;

			Buffer inputBuffer_;

			Buffer outputBuffer_;

			boost::any context_;

			bool reading_;
		};

		typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
	}
}

#endif