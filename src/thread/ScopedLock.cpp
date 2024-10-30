/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** ScopedLock
*/

#include "thread/ScopedLock.hpp"

ScopedLock::ScopedLock(IMutex &mutex) :
    _mutex(mutex)
{
    _mutex.lock();
}

ScopedLock::~ScopedLock()
{
    _mutex.unlock();
}