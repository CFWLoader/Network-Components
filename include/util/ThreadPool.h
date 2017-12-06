#ifndef __SORAN_THREADPOOL__
#define __SORAN_THREADPOOL__

#include <vector>
#include <queue>
#include <functional>

namespace soran
{
	namespace util
	{
		class Thread;

		class ThreadPool
		{
		public:

			ThreadPool(unsigned int = 1);

			~ThreadPool();

			int shutdownAll();

			int joinAll();

			int submit(const std::function<void()>&);

		private:

			std::vector<Thread*> threads_;

			std::queue<std::function<void()>> tasksQueue_;

			bool shutdownSignal_;

		};
	}
}

#endif