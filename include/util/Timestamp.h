#ifndef UTIL_TIMESTAMP_H_
#define UTIL_TIMESTAMP_H_

#include <nc/util/copyable.h>
#include <nc/util/Types.h>

#include <operators.hpp>		// Fake headers. It will fixed after I evaluate the implementation diffculty of the boost/operators.hpp.

namespace nc
{
	class Timestamp : public nc::copyable
	{};
}

#endif