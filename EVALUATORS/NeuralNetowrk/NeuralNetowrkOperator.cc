#include "NeuralNetworkOperator.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <random>

float forwardPass(const InputTensor& input);

void initializeBiases(const std::string& fileName, size_t numBiases){
    std::ofstream outputStream;
    outputStream.open(fileName);

    if (!outputStream.is_open()){std::cout << "[0][DEBUG][NeuralNetworkOperator::resetBiases]\n"; return;}

    for (int i = 0; i < numBiases; i++)
        {
            outputStream << "0\n";
        }

    outputStream.close();

}

void initializeWeightsRelu(const std::string& fileName, size_t inputNeurons, size_t outputNeurons){
    std::ofstream outputStream;
    outputStream.open(fileName);
    size_t numWeights = inputNeurons * outputNeurons;

    if (!outputStream.is_open()){std::cout << "[0][DEBUG][NeuralNetworkOperator::initializeWeightsRelu]\n"; return;}

    // Initialize weights with a normal distribution:   w ~ N(0, sqrt(2/n_in))
    float stddev = std::sqrt(2.0f / inputNeurons);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dis(0.0f, stddev);

    for (size_t i = 0; i < numWeights; ++i) {
        outputStream << dis(gen) << "\n";
    }
}

