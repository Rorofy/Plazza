/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <string>
#include <memory>
#include <stddef.h>

class Pizza {

    public:
        enum PizzaType {
            Regina = 1,
            Margarita = 2,
            Americana = 4,
            Fantasia = 8
        };

        enum PizzaSize {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };

        enum Ingredient {
            Gruyere,
            Ham,
            Mushrooms,
            Tomato,
            Doe,
            Eggplant,
            ChiefLove,
            Steak,
            GoatCheese,

            IngredientAmont
        };

        Pizza(PizzaType type, size_t time);
        ~Pizza();

        static std::string pack(const Pizza &);
        static std::shared_ptr<Pizza> unpack(const std::string &str);
        PizzaType getType(void) const;
        size_t getTime(void) const;


    private:
        PizzaType _type;
        size_t _time;
};

#endif /* !PIZZA_HPP_ */