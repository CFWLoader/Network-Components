#ifndef UTIL_COUNTDOWNLATCH_H_
#define UTIL_COUNTDOWNLATCH_H_

#include <nc/util/Condition.h>
#include <nc/util/Mutex.h>

#include <nc/util/Noncopyable.hpp>

namespace nc
{
	class CountDownLatch : util::Noncopyable
	{
	public:

		explicit CountDownLatch(int)

		void wait();

		void countDown();

		int getCount() const;
		
	private:

		mutable MutexLock mutex_;

		util::Condition condition_;

		int count_;
	};
}

#endif