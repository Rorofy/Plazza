/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Thread
*/

#include "thread/Thread.hpp"

Thread::Thread() :
    _state(READY)
{
}

Thread::~Thread()
{
    if (_state == Thread::ALIVE) stop(NULL);
}

static void *_innerRoutine(void *arg)
{
    Thread *thread = static_cast<Thread*>(arg);

    thread->_provider->provide();
    thread->_state = Thread::READY;
    return NULL;
}

void Thread::start(void *(*routine)(void*), void *arg)
{
    if (_state != Thread::READY) return;
    pthread_create(&_thread, NULL, routine, arg);
    _state = Thread::ALIVE;
}

void Thread::startProvider(std::shared_ptr<IProvider> provider)
{
    if (_state != Thread::READY) return;
    _provider = provider;
    _state = Thread::ALIVE;
    pthread_create(&_thread, NULL, _innerRoutine, this);
}

void *Thread::wait(void)
{
    void *code;

    if (_state != Thread::ALIVE) return NULL;
    pthread_join(_thread, &code);
    _state = Thread::DEAD;
    return code;
}

void Thread::stop(void *ret)
{
    if (_state != Thread::ALIVE) return;
    _state = Thread::DEAD;
    pthread_exit(ret);
}

Thread::thread_state_t Thread::getState(void) const
{
    return _state;
}