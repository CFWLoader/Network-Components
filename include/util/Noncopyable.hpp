#ifndef NONCOPYABLE_HPP_
#define NONCOPYABLE_HPP_

#include "GlobalConfigurations.h"

namespace nc
{
	namespace util
	{
		class Noncopyable
		{
			public:
				Noncopyable(){}
				~Noncopyable(){}
#ifdef CPP11
				Noncopyable(const Noncopyable&) = delete;
				Noncopyable& operator=(const Noncopyable&) = delete;
#else
			private:
				Noncopyable(const Noncopyable&){}
				Noncopyable& operator=(const Noncopyable&){}
#endif
		};
	}
}

#endif
