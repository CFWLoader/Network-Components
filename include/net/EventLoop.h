#ifndef NET_EVENT_LOOP_H_
#define NET_EVENT_LOOP_H_

#include <vector>
#include <functional>
#include <memory>

#include <boost/any.hpp>				// Waiting for fix

#include <nc/util/Noncopyable.hpp>
#include <nc/util/Mutex.h>
#include <nc/util/CurrentThread.h>
#include <nc/util/Timestamp.h>
#include <nc/net/Callbacks.h>
#include <nc/net/TimerId.h>

namespace nc
{
	namespace net
	{
		class Channel;

		class Poller;

		class TimerQueue;

		class EventLoop : nc::util::Noncopyable
		{
		public:

			typedef std::function<void()> Functor;

			EventLoop();

			~EventLoop();

			void loop();

			void quit();

			Timestamp pollReturnTime() const
			{
				return pollReturnTime_;
			}

			int64_t iteration() const
			{
				return iteration_;
			}

			void runInLoop(const Functor& cb);

			void queueInLoop(const Functor& cb);

			size_t queueSize() const;

			void runInLoop(const Functor&& cb);

			void queueInLoop(const Functor&& cb);

			TimerId runAt(const Timestamp& time, const TimerCallback& cb);

			TimerId runAfter(double delay, const TimerCallback& cb);

			TimerId runEvery(double interval, const TimerCallback& cb);

			void cancel(TimerId timerid);

			TimerId runAt(const Timestamp& time, TimerCallback&& cb);

			TimerId runAfter(double delay, const TimerCallback&& cb);

			TimerId runEvery(double interval, TimerCallback&& cb);

			void wakeup();

			void updateChannel(Channel* channel);

			void removeChannel(Channel* channel);

			bool hasChannel(Channel* channel);

			void assertInLoopThread()
			{
				if(!isInLoopThread())
				{
					abortNotInLoopThread();
				}
			}

			bool isInLoopThread() const
			{
				return threadId_ == CurrentThread::tid();
			}

			bool eventHandling() const
			{
				return eventHandling_;
			}

			void setConext(const boost::any& context);

			boost::any* getMutableContext();

			static EventLoop* getEventLoopOfCurrentThread();

		private:

			void abortNotInLoopThread();

			void handleRead();

			void doPendingFunctors();

			void printActiveChannels() const;

			typedef std::vector<Channel*> ChannelList;

			bool looping_;

			bool quit_;

			bool eventHandling_;

			bool callingPendingFunctors_;

			int64_t iteration_;

			const pid_t threadId_;

			Timestamp pollReturnTime_;

			std::scoped_ptr<Poller> poller_;

			std::scoped_ptr<TimerQueue> timerQueue_;

			int wakeupFd_;

			std::scoped_ptr<Channel> wakeupChannel_;

			boost::any context_;

			ChannelList activeChannels_;

			Channel* currentActiveChannel_;

			MutexLock mutex_;

			std::vector<Functor> pendingFunctors_;
		};
	}
}

#endif