/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** ScopedLock
*/

#ifndef SCOPEDLOCK_HPP_
#define SCOPEDLOCK_HPP_

#include "thread/IMutex.hpp"

class ScopedLock {
    public:
        ScopedLock(IMutex &mutex);
        virtual ~ScopedLock();

    protected:
        IMutex &_mutex;
};

#endif /* !SCOPEDLOCK_HPP_ */
