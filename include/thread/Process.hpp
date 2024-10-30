/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <sys/types.h>
#include <unistd.h>
#include "thread/IProvider.hpp"

class Process {
    public:
        typedef enum process_state_e
        {
            READY,
            ALIVE,
            DEAD
        } process_state_t;

        Process(IProvider &provider);
        ~Process();

        void start(void);
        void wait(void);
        void stop(void);

        process_state_t getState(void) const;
    protected:
        pid_t _pid;
        process_state_t _state;
        IProvider &_provider;
};

#endif /* !PROCESS_HPP_ */