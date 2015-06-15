#ifndef FILEUTILITIES_H_
#define FILEUTILITIES_H_

#include "GlobalConfigurations.h"

#include <stdio.h>
#include <string>

#include "Noncopyable.hpp"

namespace clown
{
	namespace utilities
	{
		class AppendLogger : public Noncopyable
		{
		public:

			explicit AppendLogger(const std::string&);

			size_t append(const char*, const size_t);

			void flush();

			~AppendLogger();

		private:

			size_t write(const char*, const size_t);

			FILE* file;

			size_t writtenBytes;

			char buffer[64 * 1024];
		};
	}
}

#endif