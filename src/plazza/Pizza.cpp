/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Pizza
*/

#include <regex>
#include "plazza/Pizza.hpp"

Pizza::Pizza(Pizza::PizzaType type, size_t time) :
    _type(type),
    _time(time)
{
}

Pizza::~Pizza()
{
}


std::string Pizza::pack(const Pizza &pizza)
{
    return std::to_string(pizza.getType()) + " " + std::to_string(pizza.getTime());
}

std::shared_ptr<Pizza> Pizza::unpack(const std::string &str)
{
    std::shared_ptr<Pizza> ptr;
    std::regex regex("^([1-9][0-9]*) ([1-9][0-9]*)$");
    std::smatch match;

    if (std::regex_search(str, match, regex))
        ptr = std::make_shared<Pizza>((PizzaType)std::stoi(match[1].str()),
            std::stoi(match[2].str()));
    else ptr = std::shared_ptr<Pizza>(nullptr);
    return ptr;
}

Pizza::PizzaType Pizza::getType(void) const
{
    return this->_type;
}

size_t Pizza::getTime(void) const
{
    return this->_time;
}