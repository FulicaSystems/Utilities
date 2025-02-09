#include <iostream>

#include "ai/perceptron.hpp"

int main()
{
    std::cout << "perceptron testing ====================" << std::endl;
    // Perceptron
    {
        using namespace Utils::AI;

        Perceptron p1(2, ActivationImpl::reLU);
        Perceptron p2(2, ActivationImpl::reLU);
        Perceptron p3(2, ActivationImpl::linear);

        p1.addNextPerceptron(&p3);
        p2.addNextPerceptron(&p3);

        p1.feed(0, 0.f);
        p1.feed(1, 1.f);
        p2.feed(0, 0.f);
        p2.feed(1, 1.f);
        p1.process(0);
        p2.process(1);
        std::cout << p3.process(0) << std::endl;
    }
}