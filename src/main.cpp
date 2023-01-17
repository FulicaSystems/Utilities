#include <iostream>

#include "utils/memleaks.hpp"

#include "mathematics.hpp"
#include "utils/property.hpp"

#include "utils/ai/neuralnetwork.hpp"

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
		Utils::Property<int> p{
			[this]() -> const int& { return a; },
			[this](const int& i) { a = i; }
		};
		Utils::Property<int> p2{
			[this]() -> const int& { return a; },
			nullptr
		};
	};

	Test t;
	t.p2 = 5;
	std::cout << t.p << std::endl;

	Utils::AI::NeuralNetwork ann;

	return 0;
}