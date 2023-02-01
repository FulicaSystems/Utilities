#include <iostream>

#include "utils/memleaks.hpp"

#include "mathematics.hpp"
#include "utils/property.hpp"

#include "utils/ai/perceptron.hpp"
#include "utils/ai/activation.hpp"
#include "utils/ai/neuralnetwork/mlpmodel.hpp"

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

	// artificial neural network (mlpn)
	{
		// TODO : find a better way for rng (https://stackoverflow.com/a/322995)
		srand(static_cast <unsigned> (time(0)));

		Utils::AI::NeuralNetwork::MLPModel model;
		//model.addLayer();

		Utils::AI::Perceptron p1(2, Utils::AI::ActivationImpl::tanH);
		Utils::AI::Perceptron p2(2, Utils::AI::ActivationImpl::tanH);
		Utils::AI::Perceptron p3(2, Utils::AI::ActivationImpl::tanH);

		p1.addNextPerceptron(&p3);
		p2.addNextPerceptron(&p3);

		p1.feed(0, 0.f);
		p1.feed(1, 1.f);
		p2.feed(0, 0.f);
		p2.feed(1, 1.f);
		p1.process(0);
		p2.process(1);
		std::cout << p3.process() << std::endl;
	}

	return 0;
}