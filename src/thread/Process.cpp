/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Process
*/

#include "thread/Process.hpp"

Process::Process(IProvider &provider) :
    _state(Process::READY),
    _pid(0),
    _provider(provider)
{
}

Process::~Process()
{
}

void Process::start(void)
{
    if (_state != Process::READY) return;
    _pid = fork();
    if (_pid == -1) return;
    if (_pid == 0) _provider.provide();
}

void Process::wait(void)
{
}

void Process::stop(void)
{
}