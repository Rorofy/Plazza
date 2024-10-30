/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** ThreadPool
*/

#include "thread/ThreadPool.hpp"
#include "thread/ScopedLock.hpp"

ThreadPool::ThreadPool(size_t amount)
{
    ScopedLock lock(_threadMutex);

    this->_threads.push_back(std::make_shared<Thread>());
}

ThreadPool::~ThreadPool()
{
}

std::shared_ptr<Thread> ThreadPool::threadAvailable(void)
{
    ScopedLock lock(_threadMutex);

    for (auto thread : this->_threads)
        if (thread->getState() == Thread::READY)
            return thread;
    return std::shared_ptr<Thread>(nullptr);
}

size_t ThreadPool::threadRunning(void)
{
    ScopedLock lock(_threadMutex);
    size_t amount = 0;

    for (auto thread : this->_threads)
        if (thread->getState() == Thread::ALIVE)
            amount++;
    return amount;
}