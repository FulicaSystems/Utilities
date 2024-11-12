#include <iostream>

#define CHKLK_OVERRIDE_NEW_OP
#include "utils/checkleak.hpp"

#include "mathematics.hpp"
#include "mathstream.hpp"
#include "utils/property.hpp"

#include "utils/ai/perceptron.hpp"
#include "utils/ai/activation.hpp"
#include "utils/ai/neuralnetwork/mlpmodel.hpp"

#include <Windows.h>

#include "utils/derived.hpp"

#include "utils/containers/queue.hpp"

#include "utils/multithread/threadpool.hpp"

int main()
{
	CHKLK_INIT
		CHKLK_ENTRY_SNAP

		// TODO : find a better way for rng (https://stackoverflow.com/a/322995)
		srand(static_cast <unsigned> (time(0)));

	std::cout << "mathematics testing ====================" << std::endl;
	// mathematics
	{
		std::cout << "Hello world !" << std::endl;

		vec<mat4, 2> v = { mat4::id, mat4::zo };

		std::cout << v << std::endl;

		vec<double, 4> d = { 1.f, 2, 3.f, 4.f };

		std::cout << d << std::endl;
	}

	std::cout << "property testing ====================" << std::endl;
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
	std::cout << "mlpn testing ====================" << std::endl;
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
		network.emplace_back();
		for (int i = 0; i < 2; ++i)
		{
			Layer& thisLayer = *(network.end() - 1);
			thisLayer.emplace_back(inputs.size(), ActivationImpl::reLU);
		}

		// add output layer
		network.emplace_back();
		for (int i = 0; i < 1; ++i)
		{
			// previous layer is before actual layer
			Layer& previousLayer = *(network.end() - 2);
			Layer& thisLayer = *(network.end() - 1);

			thisLayer.emplace_back(previousLayer.size(), ActivationImpl::linear);

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
	std::cout << "mlpn testing ====================" << std::endl;
	// artificial neural network (mlpn)
	{
		Utils::AI::NeuralNetwork::MLPModel model(2);
		model.addLayer(2, Utils::AI::ActivationImpl::reLU);
		model.addLayer(2, Utils::AI::ActivationImpl::reLU);
		model.addLayer(1, Utils::AI::ActivationImpl::linear);

		model.feedForward({ 0.f, 1.f });

		std::cout << model.getOutputs()[0] << std::endl;
	}
	std::cout << "backpropagation testing ====================" << std::endl;
	// mlpn back propagation (XOR problem, finding an architecture)
#if false
	{
		int epoch = 999;
		int inputNum = 2;
		int outputNum = 1;

		Utils::AI::NeuralNetwork::MLPModel model(inputNum);
		model.addLayer(2, Utils::AI::ActivationImpl::sigmoid);
		model.addLayer(outputNum, Utils::AI::ActivationImpl::sigmoid);

		using TrainingSet = std::vector<float>;

		// 2 inputs and 1 output
		TrainingSet set0 = { 0.f, 0.f, 0.f };
		TrainingSet set1 = { 1.f, 0.f, 1.f };
		TrainingSet set2 = { 0.f, 1.f, 1.f };
		TrainingSet set3 = { 1.f, 1.f, 0.f };

		std::vector<TrainingSet> sets;
		sets.emplace_back(set0);
		sets.emplace_back(set1);
		sets.emplace_back(set2);
		sets.emplace_back(set3);

		for (int i = 0; i < epoch; ++i)
		{
			for (TrainingSet& set : sets)
			{
				// input set
				std::vector<float> inputs;
				for (int j = 0; j < inputNum; ++j)
				{
					inputs.emplace_back(set[j]);
				}
				model.feedForward(inputs);

				std::cout << model.getOutputs()[0] << std::endl;

				// back propagation : process error then adjust weights
				// errors
				// compare to target output
				std::vector<float> outputs;
				for (int j = 0; j < outputNum; ++j)
				{
					outputs.emplace_back(set[inputNum + j]);
				}
				model.processErrorFromTarget(outputs);

				// adjust weights after processing every error rates
				// fit the entire model if the weights are not adjusted after the error rate calculation
				model.fitTarget();
			}
		}

		std::cout << "training finished" << std::endl;
		model.feedForward({ 1.f, 1.f });
		std::cout << model.getOutputs()[0] << std::endl;
	}
#endif
	std::cout << "backpropagation testing ====================" << std::endl;
	// mlpn back propagation
	{
		Utils::AI::NeuralNetwork::MLPModel model(2);
		model.addLayer(2, Utils::AI::ActivationImpl::sigmoid);
		model.addLayer(1, Utils::AI::ActivationImpl::sigmoid);

		model.trainFromSet(999, {
			{ 0.f, 0.f, 0.f },
			{ 1.f, 0.f, 1.f },
			{ 0.f, 1.f, 1.f },
			{ 1.f, 1.f, 0.f }
			});

		std::cout << "training finished" << std::endl;
		model.feedForward({ 1.f, 1.f });
		std::cout << model.getOutputs()[0] << std::endl;
	}

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
				//Super::Super::foo(); // A
			}
		};

		A a;
		a.foo();

		B b;
		b.foo();

		C c;
		c.foo();
	}

#if false
	// queue test
	{
		Utils::Queue<int> myQueue;
		myQueue.pushBackNode(0);
		myQueue.pushBackNode(1);
		myQueue.pushBackNode(2);
		myQueue.pushBackNode(3);
		myQueue.pushBackNode(4);

		std::cout << myQueue.frontData() << std::endl;
		std::cout << myQueue.frontData(1) << std::endl;
		std::cout << myQueue.frontData(2) << std::endl;
		std::cout << myQueue.frontData(3) << std::endl;
		std::cout << myQueue.frontData(4) << std::endl;
		//std::cout << myQueue.frontData(5) << std::endl; // out of range (assert)
	}
#endif

	// threadpool test
	{
		Utils::ThreadPool pool;

		pool.launchThreads(5);

		for (int i = 0; i < 99; ++i)
		{
			pool.addTask([i]() {
				std::cout << i << std::endl;
				});
		}

		//pool.killThreads(8);

		pool.pollMainQueue();
	}

	CHKLK_EXIT_SNAP
	CHKLK_DIFF_VERBOSE

	//int* a = new int;
	CHKLK_APP
	return 0;
}
