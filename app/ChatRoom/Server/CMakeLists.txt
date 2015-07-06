project(TcpServer)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

set(SOURCE_FILES
		TcpServer.h
		TcpServer.cpp
		ServerTrigger.cpp
	)

add_executable(runServer ${SOURCE_FILES})