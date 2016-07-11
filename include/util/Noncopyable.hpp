#ifndef UTIL_NONCOPYABLE_HPP_
#define UTIL_NONCOPYABLE_HPP_

namespace nc
{
	namespace util
	{
		class Noncopyable
		{
			public:
				Noncopyable(){}
				~Noncopyable(){}
#if __cplusplus >= 201103L
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
