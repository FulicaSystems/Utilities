#pragma once

#include "utils/ai/perceptron.hpp"

namespace Utils
{
	namespace AI
	{
		class Perceptron;

		class NeuralLayer
		{
		private:
			std::vector<Perceptron> neurons;

			NeuralLayer* _previousLayer = nullptr;
			NeuralLayer* _nextLayer = nullptr;

			Property<NeuralLayer*> previousLayer{
				nullptr,
				[this](NeuralLayer* layer) { _previousLayer = layer; _previousLayer->_nextLayer = this; }
			};
			Property<NeuralLayer*> nextLayer{
				nullptr,
				[this](NeuralLayer* layer) { _nextLayer = layer; _nextLayer->_previousLayer = this; }
			};

		public:
		};

		class NeuralNetwork
		{
		private:
			std::vector<float> inputs;
			std::vector<NeuralLayer> layers;

		public:
		};
	}
}