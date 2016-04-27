INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include/util")

LINK_DIRECTORIES("${PROJECT_BINARY_DIR}/lib/util")

FIND_PACKAGE(Threads REQUIRED)

IF (NOT Threads_FOUND)
	MESSAGE(FATAL_ERROR "Lost pthread libraries.")
ENDIF (NOT Threads_FOUND)

ADD_EXECUTABLE(AppendLoggerTest AppendLoggerTest.cpp)

TARGET_LINK_LIBRARIES(AppendLoggerTest nc_util ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE(MutexLockTest MutexLockTest.cpp)

TARGET_LINK_LIBRARIES(MutexLockTest nc_util ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE(NoncopyableTest NoncopyableTest.cpp)

ADD_EXECUTABLE(testCppCompilerVersion testCppComplierVersion.cpp)