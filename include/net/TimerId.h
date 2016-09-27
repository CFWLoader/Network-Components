#ifndef NET_TIMERID_H_
#define NET_TIMERID_H_

#include <nc/util/Copyable.hpp>

namespace nc
{
	namespace net
	{
		class Timer;

		class TimerId : nc::util::Copyable
		{
		public:

			TimerId() :
				timer(NULL),
				sequence_(0)
			{}

			TimerId(Timer* timer, int64_t seq) :
				timer_(timer),
				sequence_(seq)
			{}

			friend class TimerQueue;

		private:

			Timer* timer_;

			int64_t sequence_;
		};
	}
}

#endif
