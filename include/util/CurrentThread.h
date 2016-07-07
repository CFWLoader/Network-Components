#ifndef UTIL_CURRENT_THREAD_H
#define UTIL_CURRENT_THREAD_H

#include <stdint.h>

namespace nc
{
	namespace CurrentThread
	{
		// These variables are interval for a thread.(Thread.cpp)
		extern __thread int t_CacheTid;
		extern __thread char t_tidString[32];
		extern __thread int t_tidStringLength;
		extern __thread const char* t_threadName;

		void cacheId();

		inline int tid()
		{}
	}
}