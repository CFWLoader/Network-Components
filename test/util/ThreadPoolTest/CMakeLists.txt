LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib/util)

SET(SOURCE_FILES ThreadPoolTest.cpp)

ADD_EXECUTABLE(threadpool_test ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(threadpool_test soran_util)