#ifndef NET_TIMERQUEUE_H_
#define NET_TIMERQUEUE_H_

#include <set>
#include <vector>

#include <nc/util/Noncopyable.hpp>
#include <nc/util/Mutex.h>
#include <nc/util/Timestamp.h>
#include <nc/net/Callbacks.h>
#include <nc/net/Channel.h>

namespace nc
{
	namespace net
	{
		class EventLoop;

		class Timer;

		class TimerId;

		class TimerQueue : nc::util::Noncopyable
		{
		public:

			TimerQueue(EventLoop* loop);

			~TimerQueue();

			TimerId addTimer(const TimerCallback& cb,
				Timestamp when,
				double interval);

			TimerId addTimer(TimerCallback&& cb,
				Timestamp when,
				double interval);

			void cancel(TimerId timerId);

		private:

			typedef std::pair<Timestamp, Timer*> Entry;
			typedef std::set<Entry> TimerList;
			typedef std::pair<Timer*, int64_t> ActiveTimer;
			typedef std::set<ActiveTimer> ActiveTimerSet;

			void addTimerInLoop(Timer* timer);

			void cancelInLoop(TimerId timerId);

			void handleRead();

			std::vector<Entry> getExpired(Timestamp now);

			void reset(const std::vector<Entry>& expired, Timestamp now);

			bool insert(Timer* timer);

			EventLoop* loop_;

			const int timerfd_;

			Channel timerfdChannel_;

			TimerList timers_;

			ActiveTimerSet activeTimers_;

			bool callingExpiredTimers_;

			ActiveTimerSet cancelingTimers_;

		};
	}
}

#endif