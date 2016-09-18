#ifndef NET_CALLBACKS_H_
#define NET_CALLBACKS_H_

#include <funtional>
#include <memory>

#include <nc/util/Timestamp.h>

namespace nc
{
	template<typename To, typename From>
	inline std::shared_ptr<To> down_pointer_cast(const std::shared_ptr<From>& f)
	{
		if(false)
		{
			implicit_cast<From*, To*>(0);
		}

#ifndef NDEBUG
		assert(f == NULL || dynamic_cast<To*>(get_pointer(f)) != NULL);
#endif

		return static_cast<To*>(f);
	}

	namespace net
	{
		
	}
}

#endif