#include <iostream>

#include "ai/activation.hpp"
#include "ai/neural_network/mlpmodel.hpp"
#include "ai/perceptron.hpp"

int main()
{
    // finding an architecture
    {
        using namespace Utils::AI;

        // MLPModel (finding an architecture)
        using Layer = std::vector<Perceptron>;

        std::vector<Layer> network;

        // input layer
        std::vector<float> inputs;
        inputs.resize(2);

        // add hidden layer
        network.emplace_back();
        for (int i = 0; i < 2; ++i)
        {
            Layer &thisLayer = *(network.end() - 1);
            thisLayer.emplace_back(inputs.size(), ActivationImpl::reLU);
        }

        // add output layer
        network.emplace_back();
        for (int i = 0; i < 1; ++i)
        {
            // previous layer is before actual layer
            Layer &previousLayer = *(network.end() - 2);
            Layer &thisLayer = *(network.end() - 1);

            thisLayer.emplace_back(previousLayer.size(), ActivationImpl::linear);

            // link to previous layer
            for (int j = 0; j < previousLayer.size(); ++j)
            {
                previousLayer[j].addNextPerceptron(&thisLayer[i]);
            }
        }

        // feed forward
        inputs[0] = 0.f;
        inputs[1] = 1.f;

        // feed first layer with inputs
        Layer &firstLayer = network[0];
        for (int i = 0; i < firstLayer.size(); ++i)
        {
            for (int j = 0; j < inputs.size(); ++j)
            {
                firstLayer[i].feed(j, inputs[j]);
            }
        }

        // process network
        for (Layer &layer : network)
        {
            for (int i = 0; i < layer.size(); ++i)
            {
                layer[i].process(i);
            }
        }

        std::cout << network[1][0].output << std::endl;
    }

    // artificial neural network (mlpn)
    {
        Utils::AI::NeuralNetwork::MLPModel model(2);
        model.addLayer(2, Utils::AI::ActivationImpl::reLU);
        model.addLayer(2, Utils::AI::ActivationImpl::reLU);
        model.addLayer(1, Utils::AI::ActivationImpl::linear);

        model.feedForward({0.f, 1.f});

        std::cout << model.getOutputs()[0] << std::endl;
    }

    // mlpn back propagation (XOR problem, finding an architecture)
    {
        int epoch = 999;
        int inputNum = 2;
        int outputNum = 1;

        Utils::AI::NeuralNetwork::MLPModel model(inputNum);
        model.addLayer(2, Utils::AI::ActivationImpl::sigmoid);
        model.addLayer(outputNum, Utils::AI::ActivationImpl::sigmoid);

        using TrainingSet = std::vector<float>;

        // 2 inputs and 1 output
        TrainingSet set0 = {0.f, 0.f, 0.f};
        TrainingSet set1 = {1.f, 0.f, 1.f};
        TrainingSet set2 = {0.f, 1.f, 1.f};
        TrainingSet set3 = {1.f, 1.f, 0.f};

        std::vector<TrainingSet> sets;
        sets.emplace_back(set0);
        sets.emplace_back(set1);
        sets.emplace_back(set2);
        sets.emplace_back(set3);

        for (int i = 0; i < epoch; ++i)
        {
            for (TrainingSet &set : sets)
            {
                // input set
                std::vector<float> inputs;
                for (int j = 0; j < inputNum; ++j)
                {
                    inputs.emplace_back(set[j]);
                }
                model.feedForward(inputs);

                std::cout << model.getOutputs()[0] << std::endl;

                // back propagation : process error then adjust weights
                // errors
                // compare to target output
                std::vector<float> outputs;
                for (int j = 0; j < outputNum; ++j)
                {
                    outputs.emplace_back(set[inputNum + j]);
                }
                model.processErrorFromTarget(outputs);

                // adjust weights after processing every error rates
                // fit the entire model if the weights are not adjusted after the error rate calculation
                model.fitTarget();
            }
        }

        std::cout << "training finished" << std::endl;
        model.feedForward({1.f, 1.f});
        std::cout << model.getOutputs()[0] << std::endl;
    }

    // mlpn back propagation
    {
        Utils::AI::NeuralNetwork::MLPModel model(2);
        model.addLayer(2, Utils::AI::ActivationImpl::sigmoid);
        model.addLayer(1, Utils::AI::ActivationImpl::sigmoid);

        model.trainFromSet(999, {{0.f, 0.f, 0.f}, {1.f, 0.f, 1.f}, {0.f, 1.f, 1.f}, {1.f, 1.f, 0.f}});

        std::cout << "training finished" << std::endl;
        model.feedForward({1.f, 1.f});
        std::cout << model.getOutputs()[0] << std::endl;
    }
}