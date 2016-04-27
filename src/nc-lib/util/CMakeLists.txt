SET(UTIL_PKG_SRC_LIST 
	File.cpp
	MutexLock.cpp
	ClownThread.cpp
	ThreadPool.cpp
)

# FIND_PACKAGE(Threads REQUIRED)

# IF (NOT Threads_FOUND)
#	MESSAGE(FATAL_ERROR "No posix thread in this system.")
# ENDIF (NOT Threads_FOUND)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/util)

ADD_LIBRARY(nc_util SHARED ${UTIL_PKG_SRC_LIST})

# TARGET_LINK_LIBRARIES(nc_util ${Threads_LIBRARAY})

ADD_SUBDIRECTORY(test ${PROJECT_BINARY_DIR}/test/util)