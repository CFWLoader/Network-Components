#ifndef LOGFILE_H_
#define LOGFILE_H_

#include <memory>

#include "File.h"

namespace nc
{
	namespace util
	{
		class LogFile : public Noncopyable
		{
		public:
		private:

			std::unique_ptr<basis::AppendFile> appendFile;
		};
	}
}

#endif