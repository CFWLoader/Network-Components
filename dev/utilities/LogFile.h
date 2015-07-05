#ifndef LOGFILE_H_
#define LOGFILE_H_

#include <memory>

#include "File.h"

namespace clown
{
	namespace utilities
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