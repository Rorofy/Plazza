/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <functional>
#include <unordered_map>
#include <plazza/Pizza.hpp>
#include <thread/NamedPipe.hpp>
#include <memory>
#include <vector>

typedef std::function<std::shared_ptr<Pizza> ()> pizza_factory;

class Reception {
    public:
        Reception(size_t cookMod, size_t cookAmount, size_t refillTime);
        ~Reception();

        void order_pizza(std::string const &line, size_t amount);
        void create_kitchen(void);
        std::string sendToKitchen(size_t index, const std::string &line);
        int getKitchen(void);
        std::string kitchenStatus(void);
    private:
        std::unordered_map<std::string, pizza_factory> _factory;
        std::vector<std::pair<std::shared_ptr<NamedPipe>,
            std::shared_ptr<NamedPipe>>> _pipes;

    private:
        size_t _cookMod;
        size_t _cookAmount;
        size_t _refillTime;
};

#endif /* !RECEPTION_HPP_ */