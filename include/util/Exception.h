#ifndef UTIL_EXCEPTION_H_
#define UTIL_EXCEPTION_H_

#include <nc/util/Types.h>
#include <exception>

namespace nc
{
	class Exception : public std::exception
	{

	public:

		explicit Exception(const char* what);

		explicit Exception(const string& what);

		virtual ~Exception() throw();

		virtual const char* what() const throw();

		const char* stackTrace() const throw();

	private:

		void fillStackTrace();

		string message_;

		string stack_;
	};
}

#endif