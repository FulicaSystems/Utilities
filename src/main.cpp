#include <iostream>

#include "utils/memleaks.hpp"

#include "mathematics.hpp"
#include "utils/property.hpp"

int main()
{
	std::cout << "Hello world !" << std::endl;

	vec<mat4, 2> v = { mat4::id, mat4::zo };

	std::cout << v << std::endl;

	vec<double, 4> d = { 1.f, 2, 3.f, 4.f };

	std::cout << d << std::endl;

	class Test
	{
	private:
		int a;
	public:
		Property<int> p{
			[]() -> const int& { return 1; },
			[](const int& i) { std::cout << "setting to " << i << std::endl; }
		};
	};

	Test t;
	t.p = 5;
	std::cout << t.p << std::endl;

	return 0;
}