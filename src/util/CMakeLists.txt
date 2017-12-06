SET(COMPILE_LIST
        Thread.cpp
        ThreadPool.cpp
        )

ADD_LIBRARY(soran_util SHARED ${COMPILE_LIST})

TARGET_LINK_LIBRARIES(soran_util pthread)