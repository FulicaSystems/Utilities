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
		network.emplace_back();
		for (int i = 0; i < numPerceptron; ++i)
		{
			Layer& thisLayer = *(network.end() - 1);
			thisLayer.emplace_back(inputLayerSize, func);
		}

		return;
	}

	network.emplace_back();
	// prevent reallocation when pushing back
	(*(network.end() - 1)).reserve(numPerceptron);
	for (int i = 0; i < numPerceptron; ++i)
	{
		// previous layer is before actual layer
		Layer& previousLayer = network[network.size() - 2];
		Layer& thisLayer = network[network.size() - 1];

		thisLayer.emplace_back(previousLayer.size(), func);

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
		outputs.emplace_back(p.output);
	}

	return outputs;
}

void Utils::AI::NeuralNetwork::MLPModel::processErrorFromTarget(const std::vector<float>& targetOutputs, const bool bAdjustWeight)
{
	// process error rate from output layer to first hidden layer
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

			if (bAdjustWeight)
			{
				// adjust weights of the perceptron directly after processing its error rate
				// do not combine with global error fit
				// influences back propagation
				thisPerceptron.adjustWeights(alpha);
			}
		}
	}
}

void Utils::AI::NeuralNetwork::MLPModel::fitTarget()
{
	for (Layer& layer : network)
	{
		for (Perceptron& p : layer)
		{
			p.adjustWeights(alpha);
		}
	}
}

void Utils::AI::NeuralNetwork::MLPModel::trainFromSet(const int epoch, const TrainingSet& sets, const bool bAfterward)
{
	int inputNum = inputLayerSize;

	const Layer& outputLayer = *(network.end() - 1);
	int outputNum = outputLayer.size();

	for (int i = 0; i < epoch; ++i)
	{
		for (const TrainingSheet& sheet : sets)
		{
			// input set
			std::vector<float> inputs;
			for (int j = 0; j < inputNum; ++j)
			{
				inputs.emplace_back(sheet[j]);
			}
			// feed training inputs
			feedForward(inputs);

			// back propagation : process error then adjust weights
			// errors
			// compare to target output
			std::vector<float> outputs;
			for (int j = 0; j < outputNum; ++j)
			{
				outputs.emplace_back(sheet[inputNum + j]);
			}
			processErrorFromTarget(outputs, !bAfterward);

			if (bAfterward)
			{
				// adjust weights after processing every error rates
				// fit the entire model if the weights are not adjusted after the error rate calculation
				fitTarget();
			}
		}
	}
}