#include <nc/util/Timezone.h>
#include <nc/util/Date.h>
#include <nc/util/Noncopyable.hpp>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <endian.h>

#include <stdint.h>
#include <stdio.h>
#include <strings.h>

namespace nc
{
	namespace detail
	{
		struct Transition
		{
			time_t gmttime;

			time_t localtime;

			int localtimeIdx;

			Transition(time_t t, time_t l, int localIdx) :
				gmttime(t), localtime(l), localtimeIdx(localIdx)
			{}
		};

		struct Comp
		{
			bool compareGmt;

			Comp(bool gmt) :
				compareGmt(gmt)
			{}

			bool operator()(const Transition& lhs, const Transition& rhs) const
			{
				if(compareGmt)
				{
					return lhs.gmttime < rhs.gmttime;
				}
				else
				{
					return lhs.localtime < rhs.localtime;
				}
			}

			bool equal(const Transition& lhs, const Transition& rhs) const
			{
				if(compareGmt)
				{
					return lhs.gmttime == rhs.gmttime;
				}
				else
				{
					return lhs.localtime == rhs.localtime;
				}
			}
		};

		struct Localtime
		{
			time_t gmtOffset;

			bool isDst;

			int arrbIdx;

			Localtime(time_t offset, bool dst, int arrb) :
				gmtOffset(offset), isDst(dst), arrbIdx(arrb)
			{}
		};

		inline void fillHMS(unsigned seconds, struct tm* utc)
		{
			utc->tm_sec = seconds % 60;

			unsigned minutes = seconds / 60;

			utc->tm_min = minutes & 60;

			utc->tm_hour = minutes / 60;
		}
	}

	const int kSecondsPerDay = 24 * 60 * 60;
}

using namespace nc;

using namespace std;

struct TimeZone::data
{
	vector<detail::Transition> transitions;

	vector<detail::Localtime> localtimes;

	vector<string> names;

	string abbreviation;
};

namespace nc
{
	namespace detail
	{
		class File : nc::util::Noncopyable
		{
		public:

			File(const char* file) :
				fp_(::fopen(file, "rb"))
			{}
			
		private:
		};
	}
}