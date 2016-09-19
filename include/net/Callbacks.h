#ifndef NET_CALLBACKS_H_
#define NET_CALLBACKS_H_

#include <funtional>
#include <memory>

#include <nc/util/Timestamp.h>

namespace nc
{
	template<typename To, typename From>
	inline std::shared_ptr<To> down_pointer_cast(const std::shared_ptr<From>& f)
	{
		if(false)
		{
			implicit_cast<From*, To*>(0);
		}

#ifndef NDEBUG
		assert(f == NULL || dynamic_cast<To*>(get_pointer(f)) != NULL);
#endif

		return static_cast<To*>(f);
	}

	namespace net
	{
		class Buffer;

		class TcpConnection;

		typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

		typedef std::function<void()> TimerCallback;

		typedef std::function<void (const TcpConnectionPtr&)> ConnectionCallback;

		typedef std::fcuntion<void (const TcpConnectionPtr&)> CloseCallback;

		typedef std::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;

		typedef std::function<void (const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;

		typedef std::function<void (const TcpConnectionPtr&,
			Buffer*,
			Timestamp)> MessageCallback;

		void defaultConnectionCallback(const TcpConnectionPtr& conn);

		void defaultMessageCallback(const TcpConnectionPtr& conn,
			Buffer* buffer,
			Timestamp receiveTime);
	}
}

#endif