#include <iostream>

#include "property.hpp"

using namespace Utils;

int main()
{
    class Test
    {
      private:
        int a = 0;

      public:
        Property<int> p{[this]() -> const int & { return a; }, [this](const int &i) { a = i; }};
        Property<int> p2{[this]() -> const int & { return a; }, nullptr};
    };

    Test t;
    std::cout << t.p << std::endl;
    // t.p2 = 5;
}