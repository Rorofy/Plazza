/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** IProvider
*/

#ifndef IPROVIDER_HPP_
#define IPROVIDER_HPP_

class IProvider {
    public:
        virtual ~IProvider() = default;

        virtual void provide(void) = 0;
};

#endif /* !IPROVIDER_HPP_ */