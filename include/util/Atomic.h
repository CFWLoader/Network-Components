#ifndef UTIL_ATOMIC_H_
#define UTIL_ATOMIC_H_

#include "Noncopyable.h"
#include <stdint.h>

namespace nc
{
	namespace util
	{
		template<typename T>
		class AtomicIntegerT : Noncopyable
		{
		public:

			AtomicIntegerT() : value_(0)
			{}

			

		private:

			volatile T value_;

		}
	}
}

#endif