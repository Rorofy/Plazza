/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Thread
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <pthread.h>
#include <memory>
#include "thread/IProvider.hpp"

class Thread {
    public:
        typedef enum thread_state_e
        {
            READY,
            ALIVE,
            DEAD
        } thread_state_t;

        Thread();
        ~Thread();

        void startProvider(std::shared_ptr<IProvider> provider);
        void start(void *(*routine)(void*), void *arg);
        void *wait(void);
        void stop(void *ret);

        thread_state_t _state;
        std::shared_ptr<IProvider> _provider;

        thread_state_t getState(void) const;
    private:
        pthread_t _thread;
};

#endif /* !THREAD_HPP_ */