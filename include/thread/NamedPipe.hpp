/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** NamedPipe
*/

#ifndef NAMEDPIPE_HPP_
#define NAMEDPIPE_HPP_

#include <string>
#include <fstream>

class NamedPipe {
    public:
        NamedPipe(const std::string &path);
        ~NamedPipe();

        std::string sread(void) const;
        void swrite(const std::string &str) const;

        NamedPipe &operator>>(std::string &str);
        NamedPipe &operator<<(const std::string &str);
        
    private:
        int _fd;
        std::string _path;
};

#endif /* !NAMEDPIPE_HPP_ */