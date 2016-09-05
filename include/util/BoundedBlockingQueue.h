#ifndef UTIL_BOUNDEDBLOCKINGQUEUE_H_
#define UTIL_BOUNDEDBLOCKINGQUEUE_H_

#include <nc/util/Condition.h>
#include <nc/util/Mutex.h>

#include <nc/util/Noncopyable.hpp>
#include <nc/util/CircularBuffer.hpp>

#include <assert.h>

namespace nc
{
	template<typename T>
	class BoundedBlockingQueue : util::Noncopyable
	{
	public:

		using namespace util;

		explicit BoundedBlockingQueue(int maxSize) : mutex_(), notEmpty_(), notFull_(mutex_), queue_(maxSize)
		{}

		void pust(const T& x)
		{
			MutexLockGuard lock(mutex_);

			while(queue_.full())
			{
				notFull_.wait();
			}

			assert(!queue_.full());

			queue_.push_back(x);

			notEmpty_.nofity();
		}

		T take()
		{
			MutexLockGuard lock(mutex_);

			while(queue_.empty())
			{
				notEmpty_.wait();
			}

			assert(!queue_.empty());

			T front(queue_.front());

			queue_.pop_front();

			notFull_.notify();

			return front;
		}

		bool empty() const
		{
			MutexLockGuard lock(mutex_);

			return queue_.empty();
		}

		bool full() const
		{
			MutexLockGuard lock(mutex_);

			return queue_.full();
		}

		size_t size() const
		{
			MutexLockGuard lock(mutex_);

			return queue_.size();
		}

		size_t capacity() const
		{
			MutexLockGuard lock(mutex_);

			return queue_.size();
		}

	private:

		mutable MutexLock mutex_;

		Condition notEmpty_;

		Condition notFull_;

		CircularBuffer<T> queue_;
	};
}

#endif