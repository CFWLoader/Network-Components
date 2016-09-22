#ifndef NET_EVENTLOOPTHREAD_H_
#define NET_EVENTLOOPTHREAD_H_

#include <nc/util/Condition.h>
#include <nc/util/Mutex.h>
#include <nc/util/Thread.h>
#include <nc/util/Noncopyable.hpp>

namespace nc
{
	namespace net
	{
		class EventLoop;

		class EventLoopThread : nc::util::Noncopyable
		{
		public:

			typedef std::function<void(EventLoop*)> ThreadInitCallback;

			EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
				const string& name = string());

			~EventLoopThread();

			EventLoop* startLoop();
			
		private:

			void threadFunc();

			EventLoop* loop_;

			bool exiting_;

			Thread thread_;

			MutexLock mutex_;

			Condition cond_;

			ThreadInitCallback callback_;
		};
	}
}

#endif