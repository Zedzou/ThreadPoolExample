#pragma once

#include <thread>
#include <atomic>
#include <memory>
#include "taskQueue.h"

class workThread
{
    public:
        workThread(taskQueue &taskQueue);
        ~workThread();

        // 获取线程
        std::thread& getThread()
        {
            return thread_;
        }

        // 获取线程ID
        std::thread::id getId()
        {
            return thread_.get_id();
        }

        // 线程执行完成
        void finish()
        {
            finished_ = true;
        }

        // 获取当前线程执行状态
        int getState()
        {
            return state_;
        }

        // 定义线程工作状态
        constexpr static int STATE_WAIT = 1;
        constexpr static int STATE_WORK = 2;
        constexpr static int STATE_EXIT = 3;

    private:
        taskQueue &taskQueue_;
        std::thread thread_;
        std::atomic_int state_;
        std::atomic_bool finished_;
};

using threadPtr = std::shared_ptr<workThread>;