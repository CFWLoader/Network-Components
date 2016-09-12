#ifndef UTIL_LOGGING_H_
#define UTIL_LOGGING_H_

#include <nc/util/LogStream.h>
#include <nc/util/Timestamp.h>

namespace nc
{
	class TimeZone;

	class Logger
	{
	public:

		enum LogLevel
		{
			TRACE,
			DEBUG,
			INFO,
			WARN,
			ERROR,
			FATAL,
			NUM_LOG_LEVELS,
		};

		class SourceFile
		{
		public:

			template<int N>
			inline SourceFile(const char (&arr)[N]) : data_(arr), size_(N - 1)
			{
				const char* slash = strrchr(data_, '/');							// builtin function

				if (slash)
				{
					data_ = slash + 1;
					size_ -= static_cast<int>(data_ - arr);
				}
			}

			explicit SourceFile(const char* filename) : data_(filename)
			{
				const char* slash = strrchr(filename, '/');

				if(slash)
				{
					data_ = slash + 1;
				}

				size_ = static_cast<int>(strlen(data_));
			}

			const char* data_;

			int size_;
		};

		Logger(SourceFile file, int line);

		Logger(SourceFile file, int line, LogLevel level);

		Logger(SourceFile file, int line, LogLevel level, const char* func);

		Logger(SourceFile file, int line, bool toAbort);

		LogStream& stream()
		{
			return impl_.stream_;
		}
	private:
	};
}

#endif