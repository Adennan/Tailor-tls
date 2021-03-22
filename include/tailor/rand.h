#ifndef RAND_H
#define RAND_H

#include <cstdlib>
#include <ctime>
#include <iostream>

namespace tailor 
{
    std::string randSeq(int n)
    {
        std::srand(int(time(0)));
        std::string letter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string ret;
        for (i = 0; i < n; i++)
        {
            ret += letter.substr(std::rand()%(letter.size()) , 1);
        }
        return ret;
    }
}

#endif // RAND_H