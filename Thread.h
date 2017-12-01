#ifndef __SORAN_THREAD__
#define __SORAN_THREAD__

#include <thread.h>
#include <functional>

namespace soran
{
	class Thread
	{
	public:

		Thread(std::function<void()>);

		int start();

		int join();

		int detach();

	private:

		pthread_t threadId;

	};
}

#endif
