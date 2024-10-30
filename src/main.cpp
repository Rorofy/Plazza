/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** main
*/

#include <iostream>
#include "shell/Shell.hpp"

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Invalid Number of Argument" << std::endl;
        return 84;
    }
    try {
        Reception reception(std::stoi(av[1]), std::stoi(av[2]), std::stoi(av[3]));
        Shell shell(reception);

        shell.run();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}