#include <iostream>

#include "utils/memleaks.hpp"

#include "mathematics.hpp"
#include "utils/property.hpp"

#include "utils/ai/perceptron.hpp"
#include "utils/ai/activation.hpp"
#include "utils/ai/neuralnetwork/mlpmodel.hpp"

int main()
{
	// TODO : find a better way for rng (https://stackoverflow.com/a/322995)
	srand(static_cast <unsigned> (time(0)));

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
	// artificial neural network (mlpn) (finding an architecture)
	{
		using namespace Utils::AI;

		// MLPModel (finding an architecture)
		using Layer = std::vector<Perceptron>;

		std::vector<Layer> network;

		// input layer
		std::vector<float> inputs;
		inputs.resize(2);

		// add hidden layer
		network.push_back(Layer());
		for (int i = 0; i < 2; ++i)
		{
			Layer& thisLayer = *(network.end() - 1);
			thisLayer.push_back(Perceptron(inputs.size(), ActivationImpl::reLU));
		}

		// add output layer
		network.push_back(Layer());
		for (int i = 0; i < 1; ++i)
		{
			// previous layer is before actual layer
			Layer& previousLayer = *(network.end() - 2);
			Layer& thisLayer = *(network.end() - 1);

			thisLayer.push_back(Perceptron(previousLayer.size(), ActivationImpl::linear));

			// link to previous layer
			for (int j = 0; j < previousLayer.size(); ++j)
			{
				previousLayer[j].addNextPerceptron(&thisLayer[i]);
			}
		}

		// feed forward
		inputs[0] = 0.f;
		inputs[1] = 1.f;

		// feed first layer with inputs
		Layer& firstLayer = network[0];
		for (int i = 0; i < firstLayer.size(); ++i)
		{
			for (int j = 0; j < inputs.size(); ++j)
			{
				firstLayer[i].feed(j, inputs[j]);
			}
		}

		// process network
		for (Layer& layer : network)
		{
			for (int i = 0; i < layer.size(); ++i)
			{
				layer[i].process(i);
			}
		}

		std::cout << network[1][0].output << std::endl;
	}
	// artificial neural network (mlpn)
	{
		Utils::AI::NeuralNetwork::MLPModel model(2);
		model.addLayer(2, Utils::AI::ActivationImpl::reLU);
		model.addLayer(1, Utils::AI::ActivationImpl::linear);

		model.feedForward({ 0.f, 1.f });

		std::cout << model.getOutputs()[0] << std::endl;
	}

	return 0;
}