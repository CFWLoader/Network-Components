#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "Noncopyable.hpp"

namespace nc
{
	namespace util
	{
		class Thread;

		class ThreadPool : public Noncopyable
		{
		public:
		private:
			
			Thread* threads;

			int numberOfThread;
		};
	}
}

#endif
