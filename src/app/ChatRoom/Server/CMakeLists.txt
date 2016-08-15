# project(TcpServer)

# cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

FIND_PACKAGE(Threads REQUIRED)

if(not Threads_FIND)
	message(FATAL_ERROR "No Threads_lib.")
endif(not Threads_FIND)

target_link_libraries(runServer ${CMAKE_THREAD_LIBS_INIT})

set(SOURCE_FILES
		Event.h
		Event.cpp
		ClownThread.h
		ClownThread.cpp
		TcpServer.h
		TcpServer.cpp
		ServerTrigger.cpp
	)

add_executable(runServer ${SOURCE_FILES})
