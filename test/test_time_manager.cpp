#include <iostream>

#include "time_manager.hpp"

int main()
{
    Time::TimeManager tm;
    for (int i = 0; i < 99999999; ++i)
        std::cout << tm.since<Time::Epoch, uint64_t>() << " " << tm.now() << std::endl;

    return 0;
}