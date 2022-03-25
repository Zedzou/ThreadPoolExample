#include <cstdio>
#include <iostream>
#include "libThreadPool/threadPool.h"

class myTask : public taskDefinition
{
    public:

        myTask(int i, int start) : taskDefinition("myTask" + std::to_string(i)), start_(start)
        {
            std::cout << "执行任务: Hello ThreadPool" << std::endl << std::endl;
        };

        void Run()
        {
            for (int i=0; i<5; i++)
            {
                printf("---thread [%3d]: task_name= [%20s], out=%d\n", getThreadId(), getTaskName().c_str(), start_+i);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    
    private:
        int start_;
};

int main()
{
    threadPool pool;
    for (int i=0; i<50; i++){
        pool.addTask(std::make_shared<myTask>(i, i));
    }
    int i=100;
    while(i<150)
    {
        pool.addTask(std::make_shared<myTask>(i, i));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        i++;
    }
    pool.finish(); // 终止线程池
    return 0;
}