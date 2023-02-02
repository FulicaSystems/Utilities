#pragma once

#include <vector>

namespace Utils::AI
{
	class Perceptron;
}

namespace Utils::AI::NeuralNetwork
{
	// supervision learning
	// Multi-layer perceptron network
	class MLPModel
	{
	private:
		using Layer = std::vector<Perceptron>;

		// input layer is a std::vector<float> passed in the feedForward() function
		int inputLayerSize;
		// hidden and output layers
		std::vector<Layer> network;

	public:
		MLPModel(int inputLayerSize);

		void addLayer(const int numPerceptron, ActivationPtr func);

		void feedForward(const std::vector<float>& inputs);

		std::vector<float> getOutputs() const;
	};
}