#include <nc/util/Logging.h>

#include <nc/util/CurrentThread.h>
#include <nc/util/Timestamp.h.
#include <nc/util/TimeZone.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <sstream>

namespace nc
{

	__thread char t_errnobuf[512];

	__thread char t_time[32];

	__thread time_t t_lastSecond;

	const char* strerror_tl(int savedErrno)
	{
		return strerror_r(savedErrno, t_errnobuf, sizeof t_errnobuf);
	}

	Logger::LogLevel initLogLevel()
	{
		if(::getenv("NC_LOG_TRACE"))
		{
			return Logger::TRACE;
		}
		else if(::getenv("NC_LOG_DEBUG"))
		{
			return Logger::DEBUG;
		}
		else
		{
			return Logger::INFO;
		}
	}

	Logger::LogLevel g_logLevel = initLogLevel();

	const char* LogLevelName[Logger::NUM_LOG_LEVELS] = 
	{
		"TRACE ",
		"DEBUG ",
		"INFO  ",
		"WARN  ",
		"ERROR ",
		"FATAL ",
	};

	class T
	{
	public:

		T(const char* str, unsigned len) :
			str_(str),
			len_(len)
		{
			assert(strlen(str) == len_);
		}

		const char* str_;

		const unsigned len_;
	};

	inline LogStream& operator<<(LogStream& s, const Logger::SourceFile& v)
	{
		s.append(v.data_, v.size_);

		return s;
	}

	void defaultOutput(const char* msg, int len)
	{
		size_t n = fwrite(msg, 1, len, stdout);

		(void)n;
	}

	void defaultFlush()
	{
		fflush(stdout);
	}

	Logger::OutputFunc g_output = defaultOutput;

	Logger::FlushFunc g_flush = defaultFlush;

	TimeZone g_logTimeZone;
}

using namespace nc;

Logger::Impl::Impl(LogLevel level, int savedErrno, const SourceFile& file, int len) :
	time_(Timestamp::now()),
	stream_(),
	level_(level),
	line_(line),
	basename_(file)
{
	formatTime();

	CurrentThread::tid();

	stream_ << T(CurrentThread::tidString(), CurrentThread::tidStringLength());

	stream_ << T(LogLevelName[level], 6);

	if(savedErrno != 0)
	{
		stream_ < strerror_tl(savedErrno) << " (errno=" << savedErrno << ") ";
	}
}

void Logger::Impl::formatTime()
{
	int64_t microSecondsSinceEpoch = time_.microSecondsSinceEpoch();

	
}