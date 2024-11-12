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

		// training containers
		// the array of float is composed of inputs then ouputs
		// ex : { 0.f, 0.f, 1.f } (0.f and 0.f as input and 1.f as target output)
		using TrainingSheet = std::vector<float>;
		using TrainingSet = std::vector<TrainingSheet>;

		// input layer is a std::vector<float> passed in the feedForward() function
		int inputLayerSize;
		// hidden and output layers
		std::vector<Layer> network;

	public:
		// learning rate
		float alpha = 0.3f;

		MLPModel(int inputLayerSize);

		void addLayer(const int numPerceptron, ActivationPtr func);

		void feedForward(const std::vector<float>& inputs);

		std::vector<float> getOutputs() const;

		void processErrorFromTarget(const std::vector<float>& targetOutputs, const bool bAdjustWeight);

		/**
		 * Adjust every perceptrons' weights.
		 */
		void fitTarget();

		/**
		 * Fit the model weights with back propagation.
		 * 
		 * @param int epoch the number of epoch to learn
		 * @param TrainingSet sets the training set
		 * @param bool bAfterward, adjust weights after every perceptrons' error calculation if true
		 * adjust perceptron's weights directly after its error calculation if false
		 */
		void trainFromSet(const int epoch, const TrainingSet& sets, const bool bAfterward = false);
	};
}