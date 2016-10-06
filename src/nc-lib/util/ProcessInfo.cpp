// ProcessInfo.cpp

#include <nc/util/Processinfo.h>
#include <nc/util/CurrentThread.h>
#include <nc/util/FileUtil.h>

#include <algorithm>

#include <assert.h>
#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/times.h>

namespace nc
{
	namespace detail
	{
		__thread int t_numOpenedFiles = 0;

		int fdDIrFilter(const struct dirent* d)
		{
			if(::isdigit(d->d_name[0]))
			{
				++t_numOpenedFiles;
			}

			return 0;
		}
	}
}