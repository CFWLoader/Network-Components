#ifndef UTIL_THREADPOOL_H_
#define UTIL_THREADPOOL_H_

#include <nc/util/Condition.h>
#include <nc/util/Mutex.h>
#include <nc/util/Thread.h>
#include <nc/util/Types.h>
#include <nc/util/Noncopyable.hpp>

#include <functional>

#include <nc/auxiliary/ptr_vector.hpp>


namespace nc
{
	class ThreadPool : util::Noncopyable
	{
	public:

		typedef std::function<void()> Task;

		explicit ThreadPool(const string& nameArg = string("ThreadPool"));

		~ThreadPool();

		void setMaxQueueSize(int maxSize)
		{
			maxQueueSize_ = maxSize;
		}

		void setThreadInitCallback(const Task& cb)
		{
			threadInitCallback_ = cb;
		}

		void start(int numThreads);

		void stop();

		const string& name() const
		{
			return name_;
		}

		size_t queueSize() const;

		void run(const Task& f);

		void run(Task&& f);
		
	private:

		bool isFull() const;

		void runInThread();

		Task take();

		mutable MutexLock mutex_;

		Condtion notEmpty_;

		Condtion notFull_;

		string name_;

		Task threadInitCallback_;

		aux::ptr_vector<nc::Thread> threads_;

		std::deque<Task> queue_;

		size_t maxQueueSize_;

		bool running_;
	};
}

#endif
