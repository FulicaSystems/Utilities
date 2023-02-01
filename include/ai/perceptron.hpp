#pragma once

#include <vector>

#include "mathematics.hpp"

#include "activation.hpp"

namespace Utils::AI
{
	// neuron
	class Perceptron
	{
	private:
		struct Input
		{
			float value = 0.f;
			float weight = Math::randomf(-0.1f, 0.1f);
		};

		std::vector<Input> inputs;

		// activation function
		ActivationPtr func;

		Perceptron* nextP = nullptr;

		float sum() const;

	public:
		Perceptron(int numInput, ActivationPtr func, Perceptron* nextPerceptron = nullptr);

		void feed(int index, float input);
		float process(int selfIndex = 0) const;
	};
}