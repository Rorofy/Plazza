/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
** File description:
** NamedPipe
*/

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "thread/NamedPipe.hpp"

NamedPipe::NamedPipe(const std::string &path) :
    _path(path)
{
    if (access(path.c_str(), W_OK) == -1)
        if (mkfifo(path.c_str(), 0644) == -1)
            return;
    _fd = open(path.c_str(), O_RDWR);
}

NamedPipe::~NamedPipe()
{
    unlink(_path.c_str());
}

NamedPipe &NamedPipe::operator>>(std::string &str)
{
    str = sread();
}

NamedPipe &NamedPipe::operator<<(const std::string &str)
{
    swrite(str);
}

void NamedPipe::swrite(const std::string &str) const
{
    write(_fd, str.c_str(), str.length());
}

std::string NamedPipe::sread(void) const
{
    int BUF_SIZE = 255;
    char c_array[BUF_SIZE];
    std::string str;
    int len = 0;

    memset(c_array, 0, sizeof(char) * BUF_SIZE);
    while (true) {
        if ((len = read(_fd, c_array, BUF_SIZE)) <= 0) break;
        str += c_array;
        if (len < BUF_SIZE) break;
        memset(c_array, 0, sizeof(char) * BUF_SIZE);
    }
    return str;
}