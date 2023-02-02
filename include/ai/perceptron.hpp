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

		std::vector<Perceptron*> nextPerceptrons;

		float sum() const;

	public:
		// result of the perceptron after processing
		float output = 0.f;

		Perceptron(int numInput, ActivationPtr func);

		void addNextPerceptron(Perceptron* nextP);

		/**
		 * Set this perceptron's input value.
		 */
		void feed(int index, float input);

		/**
		 * Summum the inputs than go through activation function (do not forget to feed).
		 */
		float process(int selfIndex);
	};
}