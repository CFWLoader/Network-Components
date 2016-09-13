#ifndef UTIL_PROCESSINFO_H_
#define UTIL_PROCESSINFO_H_

#include <nc/util/StringPiece.h>
#include <nc/util/Types.h>
#include <nc/util/Timestamp.h>

#include <vector>

namespace nc
{
	namespace ProcessInfo
	{
		pid_t pid();

		string pidString();

		uid_t uid();

		string username();

		uid_t euid();

		Timestamp startTime();

		int clockTickPerSecond();

		int pageSize();

		bool isDebugBuild();				// constexpr

		string hostname();

		string procname();

		StringPiece procname(const string& stat);

		string procStatus();

		string procStat();

		string threadStat();

		string exePath();

		int openedFiles();

		int maxOpenFile();

		struct CpuTime
		{
			double userSeconds;

			double systemSeconds;

			CpuTime() : userSeconds(0.0), systemSeconds(0.0)
			{}
		};

		CpuTime cpuTime();

		int numThreads();

		std::vector<pid_t> threads();
	}
}

#endif