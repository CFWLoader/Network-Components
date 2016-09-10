#ifndef UTIL_LOGFILE_H_
#define UTIL_LOGFILE_H_

#include <nc/uitl/Mutex.h>
#include <nc/util/Types.h>

#include <nc/util/Noncopyable.hpp>

#include <memory>

namespace nc
{
	namespace FileUtil
	{
		class AppendFile;
	}

	class LogFile : util::Noncopyable
	{
	public:

		LogFile(const string& basename,
			size_t rollSize,
			bool threadSafe = true,
			int flushInterval = 3,
			int checkEveryN_ = 1024);

		~LogFile();

		void append(const char* logline, int len);

		void flush();

		bool rollFile();
		
	private:

		void append_unlocked(const char* logline, int len);

		static string getLogFileName(const string& basename, time_t* now);

		const string basename_;

		const size_t rollSize_;

		const int flushInterval_;

		const int checkEveryN_;

		int count_;

		std::scoped_ptr<MutexLock> mutex_;

		time_t startOfPeriod_;

		time_t lastRoll_;

		time_t lastFlush_;

		std::scoped_ptr<FileUtil::AppendFile> file_;

		const static int kRollPerSeconds_ = 60 * 60 * 24;
	};
}

#endif