#pragma once

#include <queue>
#include <mutex>
#include "task.h"

class taskQueue
{
    public:

        // 任务队列添加任务指针
        void addTask(taskPtr task)
        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            taskQueue_.push(task);
        }

        // 获取任务队列的大小
        size_t getTaskQueueSize()
        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            return taskQueue_.size();
        }

        // 判断任务队列是否为空
        bool isEmpty()
        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            return taskQueue_.empty();
        }

        // 获取任务队列中第一个任务
        taskPtr getTask()
        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            if(taskQueue_.empty()){return nullptr;};
            auto task = taskQueue_.front();
            taskQueue_.pop();
            return task;
        }

    private:
        std::queue<taskPtr> taskQueue_; //任务队列
        std::mutex queueMutex_; // 共享资源互斥锁
};