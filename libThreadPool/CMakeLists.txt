add_library(threadPool STATIC workThread.cpp threadPool.cpp)
target_link_libraries(threadPool pthread)

