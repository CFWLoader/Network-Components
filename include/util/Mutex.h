#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_

#include <pthread.h>

#include "Noncopyable.hpp"

namespace nc
{
	namespace util
	{
		class MutexLock : public Noncopyable
		{
		public:

			MutexLock();

			~MutexLock();

			void lock();

			void unlock();

		private:
			pthread_mutex_t theMutexLock;
		};

		class MutexLockGuard : public Noncopyable
		{
		public:
			 explicit MutexLockGuard(MutexLock&);

			 ~MutexLockGuard();
		private:

			MutexLock& theLock;
		};
	}
}

#endif