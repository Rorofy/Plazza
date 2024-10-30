/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** IMutex
*/

#ifndef IMUTEX_HPP_
#define IMUTEX_HPP_

#include <pthread.h>

class IMutex 
{
    public:
        IMutex() {};
        virtual ~IMutex(void) = default;
        virtual void lock(void) = 0;
        virtual void unlock(void) = 0;
        virtual void trylock(void) = 0;

    typedef enum mutex_state_e
    {
        UNLOCK,
        LOCK
    } mutex_state_t;
};

class Mutex : public IMutex
{
    public:
        Mutex(void);
        ~Mutex(void);

        void lock(void) override;
        void unlock(void) override;
        void trylock(void) override;

    protected:
        pthread_mutex_t *_mutex;
        mutex_state_t _state;
};

#endif /* !IMUTEX_HPP_ */