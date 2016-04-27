SET(UTIL_PKG_SRC_LIST 
	GlobalConfigurations.h
	File.h 
	File.cpp
	LogFile.h
	MutexLock.h
	MutexLock.cpp
	Noncopyable.hpp
	SystemNetEncapsulation.h
	ClownThread.h
	ClownThread.cpp
	ThreadPool.h
	ThreadPool.cpp
)

ADD_LIBRARY(nc_util SHARED ${UTIL_PKG_SRC_LIST})