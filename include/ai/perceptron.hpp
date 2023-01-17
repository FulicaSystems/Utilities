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

			float output = 0.f;
			float errorRate = 0.f;

			float TanH(const float x);

		public:
			void Process(const std::vector<Input>& inputs);
		};
	}
}

float Utils::AI::Perceptron::TanH(const float x)
{
	float ex = std::exp(x);
	float enx = std::exp(-x);

	return (ex - enx) / (ex + enx);
}

void Utils::AI::Perceptron::Process(const std::vector<Input>& inputs)
{
	// sum every inputs
	float sum = 0.f;
	for (Input i : inputs)
	{
		sum += i.value * i.weight;
	}
	// applying bias
	sum += 1.f * biasWeight;

	// activation
	output = TanH(sum);
}