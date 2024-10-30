/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Reception
*/

#include <iostream>
#include "plazza/Reception.hpp"
#include "plazza/Kitchen.hpp"
#include "thread/Process.hpp"

Reception::Reception(size_t cookMod, size_t cookAmount, size_t refillTime) :
    _cookMod(cookMod),
    _cookAmount(cookAmount),
    _refillTime(refillTime)
{
    _factory.insert({"regina", []() -> std::shared_ptr<Pizza>
        {return std::make_shared<Pizza>(Pizza::Regina, 2);}});
    _factory.insert({"margarita", []() -> std::shared_ptr<Pizza>
        {return std::make_shared<Pizza>(Pizza::Margarita, 1);}});
    _factory.insert({"americana", []() -> std::shared_ptr<Pizza>
        {return std::make_shared<Pizza>(Pizza::Americana, 2);}});
    _factory.insert({"fantasia", []() -> std::shared_ptr<Pizza>
        {return std::make_shared<Pizza>(Pizza::Fantasia, 4);}});
}

Reception::~Reception()
{
}

std::string Reception::kitchenStatus(void)
{
    std::string str = "";

    if (_pipes.size() == 0) return "No current kitchen runnings";
    for (size_t i = 0; i < _pipes.size(); i++)
        str += "Kitchen " + std::to_string(i) + ": " +
            sendToKitchen(i, "status") + '\n';
    return str;

}

std::string Reception::sendToKitchen(size_t index, const std::string &line)
{
    std::string reponse;

    *std::get<0>(_pipes[index]) << line;
    *std::get<1>(_pipes[index]) >> reponse; 
    return reponse;   
}

int Reception::getKitchen(void)
{
    size_t size = _pipes.size();
    int balance = -1;
    size_t min = 0;
    size_t cup = 0;

    if (size == 0) {
        create_kitchen();
        return 0;
    }
    for (size_t i = 0; i < _pipes.size(); i++) {
        cup = std::stoi(sendToKitchen(i, "count"));
        if (cup >= (_cookAmount * 2)) {
            continue;
        }
        if (balance == -1 || cup < min) {
            min = cup;
            balance = i;
        } 
    }
    if (balance == -1) {
        create_kitchen();
        return _pipes.size() - 1;
    }
    return balance;
}

void Reception::order_pizza(const std::string &type, size_t amount)
{
    std::shared_ptr<Pizza> pizza;

    if (_factory.find(type) == _factory.end())
        return;
    pizza = _factory[type]();
        std::cout << sendToKitchen(getKitchen(), "pizza: " + pizza->pack(*pizza))
            << std::endl;
}

void Reception::create_kitchen(void)
{
    static size_t amount = 0;
    std::string in = "/tmp/kitchen_from" + std::to_string(amount);
    std::string out = "/tmp/kitchen_to" + std::to_string(amount);
    Kitchen kitchen(_cookMod, _cookAmount, _refillTime, out, in);
    Process process(kitchen);

    process.start();
    _pipes.push_back(std::make_pair(
        std::make_shared<NamedPipe>(out),
        std::make_shared<NamedPipe>(in)));
    amount++;
}