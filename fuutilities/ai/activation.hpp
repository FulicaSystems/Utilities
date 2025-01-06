#pragma once

namespace Utils::AI
{
	// act
	typedef float (*ActivationPtr)(const float x);

	// every type of activation function
	struct ActivationImpl
	{
		static float threshold(const float x);
		static float linear(const float x);
		static float reLU(const float x);

		static float sigmoid(const float x);
		static float tanH(const float x);
	};
}