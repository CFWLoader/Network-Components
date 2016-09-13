#ifndef UTIL_THREAD_H_
#define UTIL_THREAD_H_

#include <nc/util/Atomic.h>
#include <nc/util/Types.h>
#include <nc/util/Noncopyable.hpp>

#include <functional>
#include <memory>

#include <pthread.h>

namespace nc
{
	class Thread : util::Noncopyable
	{
	public:

		typedef std::function<void()> ThreadFunc;

		explicit Thread(const ThreadFunc&, const string& name = string());

#ifdef __GXX_EXPERIMENTAL_CXX0X_
		explicit Thread(ThreadFunc&&, const string& name = string());
#endif

		~Thread();

		void start();

		int joind();

		bool started() const
		{
			return started_;
		}

		pid_t tid() const
		{
			return *tid_;
		}

		const string& name() const
		{
			return name_;
		}

		static int numCreated()
		{
			return numCreated_.get();
		}

	private:

		void setDefaultName();

		bool started_;

		bool joined_;

		pthread_t pthreadId_;

		std::shared_ptr<pid_t> tid_;

		ThreadFunc func_;

		string name_;

		static AtomicInt32 numCreated_;
	};
}


#endif