#pragma once

#include <thread>
#include <sstream>

// 获取线程的ID int
inline int getThreadId(std::thread::id tid)
{
    int id;
    std::stringstream ss;
    ss << tid;
    ss >> id;
    return id;
}

// 获取当前线程ID
inline int getThreadId()
{
    return getThreadId(std::this_thread::get_id());
}

// 获取指定线程的ID
inline int getThreadId(std::thread &thread_in)
{
    return getThreadId(thread_in.get_id());
}