#ifndef UTIL_CONDITION_H_
#define UTIL_CONDITION_H_

#include <nc/util/Mutex.h>

#include <nc/util/Noncopyable.hpp>

#include <pthread.h>

namespace nc
{
	namespace util
	{
		class Condition :: Noncopyable
		{
		public:

			 explicit Condition(MutexLock& mutex) : mutex_(mutex)
			 {
			 	MCHECK(pthread_cond_init(&pcond_, NULL));
			 }

			 ~Condition()
			 {
			 	MCHECK(pthread_cond_destory(&pcond_));
			 }

			 void wait()
			 {
			 	MutexLock::UnassignedGuard ug(mutex_);
			 	MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
			 }

			 bool waitForSeconds(double seconds);

			 void notify()
			 {
			 	MCHECK(pthread_cond_signal(&pcond_));
			 }

			 void notifyAll()
			 {
			 	MCHECK(pthread_cond_broadcast(&pcond_));
			 }

		private:

			MutexLock& mutex_;

			pthread_cond_t pcond_;

		};
	}
}

#endif