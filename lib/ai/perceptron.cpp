#include "utils/ai/perceptron.hpp"

Utils::AI::Perceptron::Perceptron(int numInput, ActivationPtr func)
	: func(func)
{
	// plus bias
	inputs.resize(numInput + 1);
	// setting bias
	(inputs.end() - 1)->value = 1.f;
}

float Utils::AI::Perceptron::sum() const
{
	float sum = 0.f;
	for (Input i : inputs)
	{
		sum += i.value * i.weight;
	}

	return sum;
}

void Utils::AI::Perceptron::addNextPerceptron(Perceptron* nextP)
{
	nextPerceptrons.emplace_back(nextP);
}

float Utils::AI::Perceptron::getInputWeight(const int inputIndex) const
{
	return inputs[inputIndex].weight;
}

void Utils::AI::Perceptron::adjustWeights(const float alpha)
{
	for (Input& i : inputs)
	{
		i.weight += alpha * delta * i.value;
	}
}

const std::vector<Utils::AI::Perceptron*>& Utils::AI::Perceptron::getNextPerceptrons() const
{
	return nextPerceptrons;
}

void Utils::AI::Perceptron::feed(int index, float input)
{
	inputs[index].value = input;
}

float Utils::AI::Perceptron::process(int selfIndex)
{
	output = (*func)(sum());

	// feed to next perceptron
	if (!nextPerceptrons.empty())
	{
		for (Perceptron* nextP : nextPerceptrons)
		{
			nextP->feed(selfIndex, output);
		}
	}

	return output;
}