#include <iostream>

#include "utils/memleaks.hpp"

#include "mathematics.hpp"
#include "utils/property.hpp"

#include "utils/ai/neuralnetwork.hpp"

int main()
{
	// mathematics
	{
		std::cout << "Hello world !" << std::endl;

		vec<mat4, 2> v = { mat4::id, mat4::zo };

		std::cout << v << std::endl;

		vec<double, 4> d = { 1.f, 2, 3.f, 4.f };

		std::cout << d << std::endl;
	}

	// property
	{
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
		std::cout << t.p << std::endl;
		//t.p2 = 5;
	}

	// artificial neural network
	{
		std::vector<float> inputs;
		inputs.push_back(0);
		inputs.push_back(0);

		int hiddenLayerNum = 2;
		int outputNum = 1;
		Utils::AI::NeuralNetwork ann = { hiddenLayerNum, outputNum };

		for (;;)
		{
			ann.feedForward(inputs);
			std::vector<float> outputs = ann.getOutputs();

			std::cout << outputs[0] << std::endl;

			ann.backPropagation();
		}
	}

	return 0;
}