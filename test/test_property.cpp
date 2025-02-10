#include <iostream>

#include "property.hpp"

using namespace Utils;

int main()
{
    class Test
    {
      private:
        int a = 0;
        int b = 3;

      public:
        Property<int, AccessorFlagE::RW> p = a;
        Property<int, AccessorFlagE::GET> p2 = b;
    };

    Test t;

    std::cout << t.p << std::endl;
    t.p = 6;
    std::cout << t.p << std::endl;

    std::cout << t.p2 << std::endl;
    // t.p2 = 3;
    std::cout << t.p2 << std::endl;
}