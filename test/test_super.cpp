#include <iostream>

#include "derived.hpp"

int main()
{
    // super test
    {
        class A
        {
          public:
            virtual void foo()
            {
                std::cout << "A" << std::endl;
            }
        };

        class B : public IDerived<B, A>
        {
          public:
            void foo()
            {
                Super::foo(); // A
                std::cout << "B" << std::endl;
            }
        };

        class C : public IDerived<C, B>
        {
          public:
            void foo()
            {
                Super::foo(); // A B
                std::cout << "C" << std::endl;

                // does not compile using g++ (ok with msvc)
                // Super::Super::foo(); // A
            }
        };

        A a;
        a.foo();

        B b;
        b.foo();

        C c;
        c.foo();
    }
}