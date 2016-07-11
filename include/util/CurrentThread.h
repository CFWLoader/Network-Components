#ifndef UTIL_CURRENT_THREAD_H_
#define UTIL_CURRENT_THREAD_H_

#include <stdint.h>

namespace nc
{
	namespace CurrentThread
	{
		// These variables are interval for a thread.(Thread.cpp)
		extern __thread int t_cacheTid;
		extern __thread char t_tidString[32];
		extern __thread int t_tidStringLength;
		extern __thread const char* t_threadName;

		void cacheTid();

		inline int tid()
		{
			if(__builtin_expect(t_cacheTid == 0, 0))
			{
				cacheTid();
			}

			return t_cacheTid;
		}

		inline const char* tidString()				// For differentiating threads in logging.
		{
			return t_tidString;
		}

		inline int tidStringLenght()				// For differentiating threads in logging.
		{
			return t_tidStringLength;
		}

		inline const char* name()
		{
			return t_threadName;
		}

		bool isMainThread();

		void sleepUsec(int64_t usec);
	}
}