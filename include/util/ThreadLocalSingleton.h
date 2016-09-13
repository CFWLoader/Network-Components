#ifndef UTIL_THREADLOCALSINGLETON_H_
#define UTIL_THREADLOCALSINGLETON_H_

#include <nc/util/Noncopyable.hpp>
#include <assert.h>
#include <pthread.h>

namespace nc
{
	template<typename T>
	class ThreadLocalSingleton : util::Noncopyable
	{
	public:

		static T& instance()
		{
			if(!t_value_)
			{
				t_value_ = new T();

				deleter_.set(t_value_);
			}

			return *t_value_;
		}

		static T* pointer()
		{
			return t_value_;
		}

	private:

		ThreadLocalSingleton();
		~ThreadLocalSingleton();

		static void destructor(void* obj)
		{
			assert(obj == t_value_)

			typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];

			T_must_be_complete_type dummy;

			(void)dummy;

			delete t_value_;

			t_value_ = 0;
		}
	};
}

#endif