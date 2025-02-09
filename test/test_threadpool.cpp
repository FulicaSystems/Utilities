#include <iostream>

#include "multithread/threadpool.hpp"

int main()
{
    // threadpool test
    {
        Utils::ThreadPool pool;

        pool.launchThreads(5);

        for (int i = 0; i < 99; ++i)
        {
            pool.addTask([i]() { std::cout << i << std::endl; });
        }

        // pool.killThreads(8);

        pool.pollMainQueue();
    }
}