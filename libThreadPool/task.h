#pragma once

#include <string>
#include <memory>

class taskDefinition
{
    public:
        taskDefinition(const std::string &name=" ") : name_(name)
        {
            // 具体执行的内务内容
        };

        std::string getTaskName()
        {
            return name_;
        };

        virtual void Run() = 0;
    
    private:
        std::string name_; // 定义任务的名字
};

using taskPtr = std::shared_ptr<taskDefinition>; // 创建指向任务的指针