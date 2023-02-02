#include "utils/ai/perceptron.hpp"

#include "utils/ai/neuralnetwork/mlpmodel.hpp"

Utils::AI::NeuralNetwork::MLPModel::MLPModel(const int inputLayerSize)
	: inputLayerSize(inputLayerSize)
{
}

void Utils::AI::NeuralNetwork::MLPModel::addLayer(const int numPerceptron, ActivationPtr func)
{
	if (network.empty())
	{
		network.push_back(Layer());
		for (int i = 0; i < numPerceptron; ++i)
		{
			Layer& thisLayer = *(network.end() - 1);
			thisLayer.push_back(Perceptron(inputLayerSize, func));
		}

		return;
	}

	network.push_back(Layer());
	for (int i = 0; i < numPerceptron; ++i)
	{
		// previous layer is before actual layer
		Layer& previousLayer = *(network.end() - 2);
		Layer& thisLayer = *(network.end() - 1);

		thisLayer.push_back(Perceptron(previousLayer.size(), func));

		// link to previous layer
		for (int j = 0; j < previousLayer.size(); ++j)
		{
			previousLayer[j].addNextPerceptron(&thisLayer[i]);
		}
	}
}

void Utils::AI::NeuralNetwork::MLPModel::feedForward(const std::vector<float>& inputs)
{
	// feed first layer with inputs
	Layer& firstLayer = network[0];
	for (int i = 0; i < firstLayer.size(); ++i)
	{
		for (int j = 0; j < inputLayerSize; ++j)
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
}

std::vector<float> Utils::AI::NeuralNetwork::MLPModel::getOutputs() const
{
	const Layer& outputLayer = *(network.end() - 1);

	std::vector<float> outputs;
	for (const Perceptron& p : outputLayer)
	{
		outputs.push_back(p.output);
	}

	return outputs;
}

void Utils::AI::NeuralNetwork::MLPModel::processErrorFromTarget(const std::vector<float>& targetOutputs)
{
	for (auto it = network.rbegin(); it != network.rend(); ++it)
	{
		Layer& layer = *it;

		for (int i = 0; i < layer.size(); ++i)
		{
			Perceptron& thisPerceptron = layer[i];
			float o = thisPerceptron.output;

			if (thisPerceptron.getNextPerceptrons().size() > 0) // hidden layer
			{
				// sum of next perceptrons' error rate
				float deltaSum = 0.f;
				for (const Perceptron* nextP : thisPerceptron.getNextPerceptrons())
				{
					deltaSum += nextP->getInputWeight(i) * nextP->delta;
				}

				thisPerceptron.delta = o * (1.f - o) * deltaSum;
			}
			else // output layer
			{
				thisPerceptron.delta = o * (1.f - o) * (targetOutputs[i] - o);
			}
		}
	}
}