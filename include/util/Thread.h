#ifndef __SORAN_THREAD__
#define __SORAN_THREAD__

#include <pthread.h>
#include <functional>

namespace soran
{
	namespace util
	{
		class Thread
		{
		public:

			Thread(std::function<void()>);

			int start();

			int join();

			int detach();

		private:

			pthread_t threadId_;

			std::function<void()> task_;

		};
	}
}

#endif
