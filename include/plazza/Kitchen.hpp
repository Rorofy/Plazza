/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <memory>
#include <map>
#include <queue>
#include "thread/ThreadPool.hpp"
#include "thread/IProvider.hpp"
#include "thread/NamedPipe.hpp"
#include "thread/IMutex.hpp"
#include "plazza/Pizza.hpp"

class Kitchen : public IProvider {
    public:
        Kitchen(size_t cookMod, size_t cookAmount, size_t refillTime,
            std::string in, std::string out);
        ~Kitchen();

        void provide(void) override;
        bool canTakeOrder(void) const;
        bool takeOrder(std::shared_ptr<Pizza> pizza);
        void refillIngredients(void);
        void loop(void);
        void com(void);
        std::string commandHandler(const std::string &command);

        Mutex _ingMutex;
        std::map<Pizza::Ingredient, size_t> _ings;
    private:
        std::unique_ptr<ThreadPool> _cooksPool;
        size_t _cookMod;
        size_t _cookAmount;
        size_t _refillTime;
        std::string _pathIn;
        std::string _pathOut;
        std::shared_ptr<NamedPipe> _in;
        std::shared_ptr<NamedPipe> _out;
        std::queue<std::shared_ptr<Pizza>> _queue;
        bool _alive;
        double _timeout;
};

#endif /* !KITCHEN_HPP_ */