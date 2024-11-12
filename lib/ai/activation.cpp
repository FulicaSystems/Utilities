#include "mathematics.hpp"

#include "activation.hpp"

float Utils::AI::ActivationImpl::threshold(const float x)
{
	float threshold = 0.f;
	return x > threshold ? 1.f : 0.f;
}

float Utils::AI::ActivationImpl::linear(const float x)
{
	return x;
}

float Utils::AI::ActivationImpl::reLU(const float x)
{
	return Math::max(0.f, x);
}

float Utils::AI::ActivationImpl::sigmoid(const float x)
{
	float beta = 10.f;
	float e = std::exp(-beta * x);

	return 1.f / (1.f + e);
}

float Utils::AI::ActivationImpl::tanH(const float x)
{
	float a = std::exp(x);
	float b = std::exp(-x);

	return (a - b) / (a + b);
}