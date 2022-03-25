#include "workThread.h"
#include "threadUtils.h"
#include <iostream>

workThread::workThread(taskQueue &taskQueue):taskQueue_(taskQueue), state_(STATE_WAIT), finished_(false)
{
    // 创建线程
    thread_ = std::thread([this]()
    {
        while(!finished_)
        {
            // 判断线程执行状态
            state_ = STATE_WAIT;
            while (!finished_ && taskQueue_.isEmpty()){
                std::this_thread::sleep_for(std::chrono::microseconds(100)); // 等待0.1s
            }
            if(finished_){break;};

            // 当前线程执行任务
            taskPtr task = taskQueue_.getTask(); // 获取队列中第一个任务
            if(task != nullptr){
                state_ = STATE_WORK;
                printf("---thread [%3d]: run task [%20s] begin\n ", getThreadId(), task->getTaskName().c_str() );
                task->Run();
                printf("---thread [%3d]: run task [%20s] end\n", getThreadId(), task->getTaskName().c_str());
            }
        }
        state_ = STATE_EXIT;
    });
    printf("---thread [%3d]: started\n", getThreadId(thread_));
};

workThread::~workThread()
{
    printf("---thread[%3d]: finished\n", getThreadId(thread_));
    if(thread_.joinable())
    {
        thread_.join();
    }
}