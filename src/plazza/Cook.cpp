/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Cook
*/

#include "plazza/Cook.hpp"

Cook::Cook(size_t time) :
    _time(time)
{
}

Cook::~Cook()
{
}

void Cook::provide(void)
{
    usleep(_time);
}