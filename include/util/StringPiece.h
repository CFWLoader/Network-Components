#ifndef UTIL_STRINGPIECE_H_
#define UTIL_STRINGPIECE_H_

#include <string.h>
#include <iosfwd>

#include <nc/util/Types.h>

#ifndef NC_STD_STRING
	#include <string>
#endif

namespace nc
{
	class StringArg
	{
	public:

		StringArg(const char* str) : str_(str)
		{}

		StringArg(const string& str) : str_(str.c_str())
		{}

#ifndef NC_STD_STRING
		StringArg(const std::string& str) : str_(str.c_str())
		{}
#endif

		const char* c_str() const 
		{
			return str_;
		}

	private:

		const char* str_;

	};

	class StringPiece
	{
	public:

		StringPiece() : ptr_(NULL), length_(0)
		{}

		StringPiece(const char* str) : ptr_(str), length_(static_cast<int>(strlen(ptr_)))
		{}

		StringPiece(const unsigned char* str) : ptr_(reinterpret_cast<const char*>(str)), length_(static_cast<int>(strlen(ptr_)))
		{}

#ifndef NC_STD_STRING
		StringPiece(const std::string& str) : ptr_(str.data()), length_(static_cast<int>(str.size()))
		{}
#endif

		StringPiece(const char* offset, int len) : ptr_(offset), length_(len)
		{}

		const char* data() const
		{
			return ptr_;
		}

		int size() const
		{
			return length_;
		}

		bool empty() const
		{
			return length_ == 0;
		}

		const char* begin() const
		{
			return ptr_;
		}

		const char* end() const
		{
			return ptr_ + length_;
		}

		void clear()
		{
			ptr_ = NULL;

			length_ = 0;
		}

		void set(const char* buffer, int len)
		{
			ptr_ = buffer;

			length_ = length_;
		}

		void set(const char* str)
		{
			ptr_ = str;

			length_ = static_cast<int>(strlen(ptr_));
		}

		void set(const void* buffer, int len)
		{
			ptr = reinterpret_cast<const char*>(buffer);

			length_ = len;
		}

		char operator[](int i) const
		{
			return ptr_[i];
		}

		void removePrefix(int n)


	private:

		const char* ptr_;

		int length_;

	}
}

#endif