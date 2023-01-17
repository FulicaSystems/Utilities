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
			NeuralLayer* _previousLayer = nullptr;
			NeuralLayer* _nextLayer = nullptr;

		public:
			std::vector<Perceptron> neurons;

			Property<NeuralLayer*> previousLayer{
				nullptr,
				[this](NeuralLayer* layer) { _previousLayer = layer; _previousLayer->_nextLayer = this; }
			};
			Property<NeuralLayer*> nextLayer{
				[this]() -> NeuralLayer* { return _nextLayer; },
				[this](NeuralLayer* layer) { _nextLayer = layer; _nextLayer->_previousLayer = this; }
			};

			NeuralLayer(const int neuronNum = 2);
		};

		class NeuralNetwork
		{
		private:
			std::vector<NeuralLayer> layers;

		public:
			NeuralNetwork(const int hiddenLayerNum, const int outputNum);

			void feedForward(const std::vector<float> inputs);
			const std::vector<float>& getOutputs() const;

			void backPropagation();
		};
	}
}

Utils::AI::NeuralLayer::NeuralLayer(const int neuronNum)
{
	for (int i = 0; i < neuronNum; ++i)
	{
		neurons.push_back(Perceptron());
	}
}

Utils::AI::NeuralNetwork::NeuralNetwork(const int hiddenLayerNum, const int outputNum)
{
	for (int i = 0; i < hiddenLayerNum; ++i)
	{
		NeuralLayer nl = NeuralLayer();
		if (i != 0)
		{
			nl.previousLayer = &layers[i - 1];
		}

		layers.push_back(nl);
	}
}

void Utils::AI::NeuralNetwork::feedForward(const std::vector<float> inputs)
{
	std::vector<float> inputsToFeed = inputs;

	for (;;)
	{
		NeuralLayer& layer = layers[0];
		for (Perceptron& neuron : layer.neurons)
		{
			neuron.feed(inputsToFeed);
		}

		if (layer.nextLayer)
		{
			break;
		}
		else
		{
			inputsToFeed = layer.getOutputs();
			layer = *layer.nextLayer;
		}
	}
}

const std::vector<float>& Utils::AI::NeuralNetwork::getOutputs() const
{
	std::vector<float> outputs;
	const NeuralLayer& outputLayer = layers.back();

	for (const Perceptron& neuron : outputLayer.neurons)
	{
		outputs.push_back(neuron.output);
	}

	return outputs;
}

void Utils::AI::NeuralNetwork::backPropagation()
{
}