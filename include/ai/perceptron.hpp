#pragma once

#include "mathematics.hpp"

namespace Utils
{
	namespace AI
	{
		/**
		 * Neuron
		 */
		class Perceptron
		{
		private:
			struct Input
			{
				float value;
				float weight;
			};

			std::vector<Input> recordedInputs;
			float biasWeight = 1.f;

			float tanH(const float x);

		public:
			float output = 0.f;
			float errorRate = 0.f;

			void feed(const std::vector<float>& inputs);
		};
	}
}

float Utils::AI::Perceptron::tanH(const float x)
{
	float ex = std::exp(x);
	float enx = std::exp(-x);

	return (ex - enx) / (ex + enx);
}

void Utils::AI::Perceptron::feed(const std::vector<float>& inputs)
{
	recordedInputs = inputs;

	// sum every inputs
	float sum = 0.f;
	for (Input i : recordedInputs)
	{
		sum += i.value * i.weight;
	}
	// applying bias
	sum += 1.f * biasWeight;

	// activation
	output = tanH(sum);
}