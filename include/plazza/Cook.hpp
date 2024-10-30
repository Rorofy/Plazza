/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <unistd.h>
#include "thread/IProvider.hpp"

class Cook : public IProvider {
    public:
        Cook(size_t time);
        virtual ~Cook();

        void provide(void) override;
    private:
        size_t _time;
};

#endif /* !COOK_HPP_ */