#ifndef NET_TIMER_H_
#define NET_TIMER_H_

#include <nc/util/Noncopyable.hpp>
#include <nc/util/Atomic.h>
#include <nc/util/TimeStamp.h>

#include <nc/net/Callbacks.h>

namespace nc
{
	namespace net
	{
		class Timer : nc::util::Noncopyable
		{
		public:

			Timer(const TimerCallback& cb, Timestamp when, double interval) :
				callback_(cb),
				expiration_(when),
				interval_(interval),
				repeat_(interval > 0.0),
				sequence_(s_numCreated.incrementAndGet())
				{}

			Timer(TimerCallback&& cb, Timestamp, double interval) :
				callback_(std::move(cb)),
				expiration_(when),
				interval_(interval),
				repeat_(interval > 0.0),
				sequence_(s_numCreated.incrementAndGet())
			{}

			void run() const
			{
				callback_();
			}

			Timestamp expiration() const
			{
				return expiration_;
			}

			bool repeat() const
			{
				return sequence_;
			}

			int64_t sequence() const
			{
				return sequence_;
			}

			void restart(Timestamp now);

			static int64_t numCreated()
			{
				return s_numCreated_.get();
			}

		private:

			const TimerCallback callback_;

			Timestamp expiration_;

			const double interval_;

			const bool repeat_;

			const int64_t sequence_;

			static AtomicInt64 s_numCreated_;
		};
	}
}

#endif