/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Mutex
*/

#include "thread/IMutex.hpp"

Mutex::Mutex(void) :
    _mutex(new pthread_mutex_t()),
    _state(IMutex::UNLOCK)
{
    pthread_mutex_init(_mutex, NULL);
}

Mutex::~Mutex(void)
{
    if (_state == LOCK) pthread_mutex_unlock(_mutex);
    pthread_mutex_destroy(_mutex);
}

void Mutex::lock(void)
{
    pthread_mutex_lock(_mutex);
    _state = IMutex::LOCK;
}

void Mutex::unlock(void)
{
    pthread_mutex_unlock(_mutex);
    _state = IMutex::UNLOCK;
}

void Mutex::trylock(void)
{
    _state = pthread_mutex_trylock(_mutex) ? IMutex::LOCK : IMutex::UNLOCK;
}