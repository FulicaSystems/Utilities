#include <iostream>

#include "containers/queue.hpp"

int main()
{
    // queue test
    {
        Utils::Queue<int> myQueue;
        myQueue.pushBackNode(0);
        myQueue.pushBackNode(1);
        myQueue.pushBackNode(2);
        myQueue.pushBackNode(3);
        myQueue.pushBackNode(4);

        std::cout << myQueue.frontData() << std::endl;
        std::cout << myQueue.frontData(1) << std::endl;
        std::cout << myQueue.frontData(2) << std::endl;
        std::cout << myQueue.frontData(3) << std::endl;
        std::cout << myQueue.frontData(4) << std::endl;
        // std::cout << myQueue.frontData(5) << std::endl; // out of range (assert)
    }
}