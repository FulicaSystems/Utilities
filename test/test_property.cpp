#include <iostream>

#include "property.hpp"

int main()
{
    {
        class Test
        {
          private:
            int a;

          public:
            Utils::Property<int> p{[this]() -> const int & { return a; }, [this](const int &i) { a = i; }};
            Utils::Property<int> p2{[this]() -> const int & { return a; }, nullptr};
        };

        Test t;
        std::cout << t.p << std::endl;
        // t.p2 = 5;
    }
}