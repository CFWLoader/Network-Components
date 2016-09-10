#ifndef UTIL_LOGSTREAM_H_
#define UTIL_LOGSTREAM_H_

#include <nc/util/StringPiece.h>
#include <nc/util/Types.h>

#include <assert.h>
#include <string.h>

#ifndef NC_STD_STRING
	#include <string>
#endif

#include <nc/util/Noncopyable.hpp>

namespace nc
{
	namespace detail
	{

		const int kSmallBuffer = 4000;
		const int kLargeBuffer = 4000 * 1000;

		template<int SIZE>
		class FixedBuffer : util::Noncopyable
		{
			
		};
	}
}

#endif