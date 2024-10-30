/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Shell
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

#include <memory>
#include "plazza/Reception.hpp"

class Shell {
    public:
        Shell(Reception &reception);
        ~Shell();

        void run(void);
        void shell_parse(std::string &line);
        bool shell_pizza_parse(std::string &line);
    
    private:
        Reception &_reception;
};

#endif /* !SHELL_HPP_ */