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

		static LogLevel logLevel();

		static void setLogLevel(LogLevel level);

		typedef void (*OutputFunc)(const char* msg, int len);
		typedef void (*FlushFunc);

		static void setOutput(OutputFunc);

		static void setFlush(FlushFunc);

		static void setTimeZone(const TimeZone& tz);

	private:

		class Impl
		{
		public:
			typedef Logger::LogLevel LogLevel;

			Impl(LogLevel level, int old_errno, const SourceFile& file, int line);

			void formatTime();

			void finish();

			Timestamp time_;

			LogStream stream_;

			LogLevel level_;

			int line_;

			SourceFile basename_;
		private:
		};

		Impl impl_;
	};

	extern Logger::LogLevel g_logLevel;

	inline Logger::LogLevel Logger::logLevel()
	{
		return g_logLevel;
	}

#define LOG_TRACE if (nc::Logger::logLevel() <= nc::Logger::TRACE) \
	nc::Logger(__FILE__, __LINE__, nc::Logger::TRACE, __func__).stream()
#define LOG_DEBUG if (nc::Logger::logLevel() <= nc::Logger::DEBUG) \
	nc::Logger(__FILE__, __LINE__, nc::Logger::DEBUG, __func__).stream()
#define LOG_INFO if (nc::Logger::logLevel() <= nc::Logger::INFO) \
	nc::Logger(__FILE__, __LINE__).stream()
#define LOG_WARN nc::Logger(__FILE__, __LINE__, nc::Logger::WARN).stream()
#define LOG_ERROR nc::Logger(__FILE__, __LINE__, nc::Logger::ERROR).stream()
#define LOG_FATAL nc::Logger(__FILE__, __LINE__, nc::Logger::FATAL).stream()
#define LOG_SYSERR nc::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL nc::Logger(__FILE__, __LINE__, true).stream()

	const char* strerror_tl(int savedErrno);

#define CHECK_NOTNULL(val) \
	::nc::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

	template<typename T>
	T* CheckNotNull(Logger::SourceFile file, int line, const char* names, T* ptr)
	{
		if (ptr == NULL)
		{
			Logger(file, line, Logger::FATAL).stream() << names;
		}

		return ptr;
	}
}

#endif