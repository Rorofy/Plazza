/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** ThreadPool
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <vector>
#include <memory>
#include "thread/Thread.hpp"
#include "thread/IMutex.hpp"

class ThreadPool {
    public:
        ThreadPool(size_t amount);
        ~ThreadPool();

        std::shared_ptr<Thread> threadAvailable(void);
        size_t threadRunning(void);
    private:
        std::vector<std::shared_ptr<Thread>> _threads;
        Mutex _threadMutex;
};

#endif /* !THREADPOOL_HPP_ */