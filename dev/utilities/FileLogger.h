#ifndef FILELOGGER_H_
#define FILELOGGER_H_

#include "GlobalConfigurations.h"

namespace clown
{
	namespace utilities
	{
		class FileLogger
		{
		public:
			enum class LogLevel
			{
				TRACE,
				DEBUG,
				INFO,
				WARNNING,
				ERROR,
				FATAL
			};
		private:
		};
	}
}

#endif