#ifndef NET_EVENTLOOPTHREADPOOL_H_
#define NET_EVENTLOOPTHREADPOOL_H_

#include <nc/util/Types.h>
#include <nc/util/Noncopyable.hpp>

#include <vector>
#include <functional>

namespace nc
{
	namespace net
	{
		class EventLoop;

		class EventLoopThread;

		class EventLoopThreadPool : nc::util::Noncopyable
		{
		public:

			typedef std::function<void(EventLoop*)> ThreadInitCallback;

			EventLoopThreadPool(EventLoop* baseLoop, const string& nameArg);

			~EventLoopThreadPool();

			void setThreadNum(int numThreads)
			{
				numThreads_ = numThreads;
			}

			void start(const ThreadInitCallback& cb = ThreadInitCallback());

			EventLoop* getNextLoop();

			EventLoop* getLoopForHash(size_t hashCode);

			std::vector<EventLoop*> getAllLoops();

			bool started() const
			{
				return started_;
			}

			const string& name() const
			{
				return name_;
			}

		private:

			EventLoop* baseLoop_;

			string name_;

			bool started_;

			int numThreads_;

			int next_;

			boost::ptr_vector<EventLoopThread> threads_;

			std::vector<EventLoop*> loops_;
		};
	}
}

#endif