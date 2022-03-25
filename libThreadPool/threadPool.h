#pragma once

#include <unordered_map>
#include "taskQueue.h"
#include "workThread.h"
#include "threadUtils.h"

class threadPool
{
    public:
        threadPool(int min=10, int max=50);
        ~threadPool();
        void finish();
        void addTask(taskPtr task);

    private:
        void addThread();
        void delThread();
        
        std::atomic_bool finished_;
        std::unordered_map<std::thread::id, threadPtr> threadPool_;
        std::thread manageThread_;
        taskQueue taskQueue_;

        int min_;
        int max_;
};