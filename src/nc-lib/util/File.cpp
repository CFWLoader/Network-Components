#include <cstdio>
#include <cerrno>
#include <cstring>

#include <File.h>

clown::basis::File::File(const std::string& filename) : 
file(::fopen(filename.c_str(), "a+e")), writtenBytes(0)
{
	if(file == nullptr)
	{
		::fprintf(stderr, "%s\n", strerror(errno));
	}
}

clown::basis::File::~File()
{
	fclose(file);
}

size_t clown::basis::File::write(const char* input, const size_t length)
{
	return ::fwrite(input, length, 1, file);
}

void clown::basis::File::flush()
{
	::fflush(file);
}

size_t clown::basis::File::append(const char* input, const size_t length)
{
	size_t writtenIndex = this->write(input, length), written = 0;

	size_t left = length - written;

	while(left > 0)
	{
		written = this->write(input + writtenIndex, length - left);

		if(written == 0)
		{
			int errorNumber = ferror(file);

			if(errorNumber)
			{
				fprintf(stderr, "Error happend in File::append().\n");
			}

			break;
		}

		writtenIndex += written;

		left = length - writtenIndex;
	}

	writtenBytes += writtenIndex;

	return writtenIndex;
}
