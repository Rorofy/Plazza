/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Shell
*/

#include <iostream>
#include <regex>
#include "plazza/Pizza.hpp"
#include "shell/Shell.hpp"

Shell::Shell(Reception &reception) :
    _reception(reception)
{
}

Shell::~Shell()
{
}

void Shell::shell_parse(std::string &line)
{
    if (line == "status") {
        std::cout << _reception.kitchenStatus() << std::endl;
    }
    else
        shell_pizza_parse(line);
}

bool Shell::shell_pizza_parse(std::string &line)
{
    std::regex regex("^([a-zA-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)$");
    std::smatch match;

    if (!std::regex_search(line, match, regex))
        return false;
    _reception.order_pizza(match[1].str(),
        std::atoi(match[3].str().c_str()));
    return true;
}

void Shell::run(void)
{
    std::pair<std::shared_ptr<Pizza>, size_t> pair;
    std::shared_ptr<Pizza> pizza;

    for (std::string line; std::getline(std::cin, line);) {
        shell_parse(line);
    }
}