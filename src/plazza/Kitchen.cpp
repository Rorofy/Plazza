/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Kitchen
*/

#include <unistd.h>
#include <chrono>
#include <thread>
#include "plazza/Kitchen.hpp"
#include "plazza/Cook.hpp"
#include "thread/ScopedLock.hpp"

Kitchen::Kitchen(size_t cookMod, size_t cookAmount, size_t refillTime,
    std::string in, std::string out) :
    _cookMod(cookMod),
    _cooksPool(std::make_unique<ThreadPool>(cookAmount)),
    _cookAmount(cookAmount),
    _refillTime(refillTime),
    _pathIn(in),
    _pathOut(out),
    _alive(true)
{
    ScopedLock lock(_ingMutex);

    for (size_t i = 0; i < Pizza::Ingredient::IngredientAmont; i++)
        _ings.insert({(Pizza::Ingredient)i,  5});
}

Kitchen::~Kitchen()
{
}

bool Kitchen::canTakeOrder(void) const
{
    auto thread = this->_cooksPool->threadAvailable();

    if (thread != nullptr) return true;
    return false;
}

bool Kitchen::takeOrder(std::shared_ptr<Pizza> pizza)
{
    auto thread = this->_cooksPool->threadAvailable();

    if (thread != nullptr) thread->startProvider(std::make_shared<Cook>
        (pizza->getTime() * _cookMod * 1000000));
    _queue.push(pizza);
    return true;
}

std::string Kitchen::commandHandler(const std::string &command)
{
    std::string str = "";
	std::map<Pizza::Ingredient, std::string> dic = {
		{Pizza::Ingredient::Doe, "Doe"},
		{Pizza::Ingredient::Ham, "Ham"},
		{Pizza::Ingredient::GoatCheese, "Goat cheese"},
		{Pizza::Ingredient::Tomato, "Tomato"},
		{Pizza::Ingredient::Gruyere, "Gruyere"},
		{Pizza::Ingredient::Mushrooms, "Mushrooms" },
		{Pizza::Ingredient::Steak, "Steak"},
		{Pizza::Ingredient::Eggplant, "Eggplant"},
		{Pizza::Ingredient::ChiefLove, "Chief love"}
	};
    if (command.rfind("pizza: ") == 0) {
        if (!canTakeOrder()) return "kitchen can't handle and break";
        takeOrder(Pizza::unpack(command.substr(std::string("pizza: ")
            .length())));
        return "Pizza start to be baked";
    }
    else if (command == "status") {
        str = "Busy cook : " + std::to_string(_cooksPool->threadRunning())
            + "/" + std::to_string(_cookAmount) + '\n';
        _ingMutex.lock();
        str += "Ingredients:\n";
        for (auto &i : _ings)
            str += dic[i.first] + " : " + std::to_string((int)i.second) + '\n';
        _ingMutex.unlock();
        return str;
    }
    else if (command == "count")
        return std::to_string(this->_cooksPool->threadRunning());
    return "No command found";
}

void Kitchen::loop(void)
{
    auto begin = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();

    while (_alive) {
        usleep(100);
        now = std::chrono::high_resolution_clock::now();
        _timeout += std::chrono::duration_cast<std::chrono::nanoseconds>
            (now - begin).count();
        if (this->_cooksPool->threadRunning() > 0) _timeout = 0;
        if (_timeout >= 5000000000) break;
    }
    _alive = false;
}

void Kitchen::com(void)
{
    std::string command;

    while (_alive) {
        *_in >> command;
        *_out << commandHandler(command);
    }
}

void Kitchen::provide(void)
{
    Thread refillThread;
    Thread kitchenThread;

    _in = std::make_shared<NamedPipe>(_pathIn);
    _out = std::make_shared<NamedPipe>(_pathOut);
    refillThread.start([](void *kitchen) -> void * {
        ((Kitchen *)kitchen)->refillIngredients();
    }, this);
    com();
/*    kitchenThread.start([](void *kitchen) -> void * {
        ((Kitchen *)kitchen)->loop();
    }, this);*/
}

void Kitchen::refillIngredients(void)
{
    while (_alive) {
        usleep(_refillTime * 1000);
        _ingMutex.lock();
        for (size_t i = 0; i < Pizza::Ingredient::IngredientAmont; i++)
            if (_ings[((Pizza::Ingredient)i)] < 5) _ings[(Pizza::Ingredient)i]++;
        _ingMutex.unlock();
    }
}