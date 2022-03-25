#include "threadPool.h"

// 管理线程
threadPool::threadPool(int min, int max):finished_(false), min_(min), max_(max)
{
    // 添加线程
    for (int i=0; i<min_; i++){
        addThread();
    }

    // 管理者线程
    manageThread_ = std::thread([this]()
    {
        while(!finished_) // 初始设置线程未执行
        {
            // 如果线程不足则添加线程
            if( taskQueue_.getTaskQueueSize() > 2*threadPool_.size() && threadPool_.size() < max_){
                addThread();
            }
            // 否则线程过多则删除线程
            else{
                // 计算等待分配任务的线程数
                int count = 0;
                for (auto &t:threadPool_){
                    if (t.second->getState() == workThread::STATE_WAIT){
                        ++count;
                    }
                }
                // 等待分配任务的线程数过多
                if(count > taskQueue_.getTaskQueueSize() && threadPool_.size() < min_){
                    delThread();
                }
            };
        };
    });
};

// 线程池--->添加线程
void threadPool::addThread()
{
    printf("--- add thread\n");
    auto workThreadPtr = std::make_shared<workThread>(taskQueue_);
    threadPool_[workThreadPtr->getId()] = workThreadPtr;
}

// 线程池--->删除线程
void threadPool::delThread()
{
    printf("--- del thread\n");
    std::thread::id tid;
    for (auto &t : threadPool_)
    {
        if(t.second->getState() == workThread::STATE_WAIT)
        {
            t.second->finish();
            tid = t.first;
            break;
        }
    }
    threadPool_.erase(tid);
}

// 线程池--->当前线程完成工作
void threadPool::finish()
{
    finished_ = true;
    for (auto &t:threadPool_)
    {
        t.second->finish();
    }
}

// 任务队列--->添加任务
void threadPool::addTask(taskPtr task)
{
    printf("---add task: [%s]\n", task->getTaskName().c_str());
    taskQueue_.addTask(task);
}

threadPool::~threadPool()
{
    if(manageThread_.joinable())
    {
        manageThread_.join();
    }
}
