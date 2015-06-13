#ifndef NONCOPYABLE_HPP_
#define NONCOPYABLE_HPP_

namespace clown{
	namespace utilities{
		class Noncopyable{
			public:
#if __cplusplus >= 201103L
				Noncopyable(const Noncopyable&) = delete;
				Noncopyable& operator=(const Noncopyable&) = delete;
#else
				Noncopyable(){}
				~Noncopyable(){}
			private:
				Noncopyable(const Noncopyable&){}
				Noncopyable& operator=(const Noncopyable&){}
#endif
		};
	}
}

#endif
