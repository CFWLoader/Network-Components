#ifndef FILEUTILITIES_H_
#define FILEUTILITIES_H_

#include "GlobalConfigurations.h"

#include <stdio.h>
#include <string>

#include "Noncopyable.hpp"

namespace clown
{
	namespace basis
	{
		using namespace utilities;

		class File : public Noncopyable
		{
		public:

			explicit File(const std::string&);

			size_t append(const char*, const size_t);

			void flush();

			~File();

		private:

			size_t write(const char*, const size_t);

			FILE* file;

			size_t writtenBytes;

			//char buffer[64 * 1024];
		};
	}
}

#endif