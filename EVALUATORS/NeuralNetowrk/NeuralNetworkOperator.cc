#include "NeuralNetworkOperator.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <random>

namespace NeuralNetworkOperator{
    

void initializeBiases(const std::string& fileName, size_t numBiases){
    std::ofstream outputStream;
    outputStream.open(fileName);

    if (!outputStream.is_open()){std::cout << "[0][DEBUG][NeuralNetworkOperator::resetBiases]\n"; return;}

    for (size_t i = 0; i < numBiases; i++)
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

    // He initialization for Relu:   w ~ N(0, sqrt(2/n_in))
    float stddev = std::sqrt(2.0f / inputNeurons);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dis(0.0f, stddev);

    for (size_t i = 0; i < numWeights; ++i) {
        outputStream << dis(gen) << "\n";
    }

    outputStream.close();
}

void initializeWeightsSigmoid(const std::string& fileName, size_t inputNeurons, size_t outputNeurons){
    std::ofstream outputStream;
    outputStream.open(fileName);
    size_t numWeights = inputNeurons * outputNeurons;

    if (!outputStream.is_open()){std::cout << "[0][DEBUG][NeuralNetworkOperator::initializeWeightsSigmoid]\n"; return;}


    // Xavier/Glorot initialization for sigmoid/tanh:     w ~ U(-sqrt(6/(n_in + n_out)), sqrt(6/(n_in + n_out)))
    float limit = std::sqrt(6.0f / (inputNeurons + outputNeurons));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-limit, limit);

    for (size_t i = 0; i < numWeights; ++i) {
        outputStream << dis(gen) << "\n";
    }

    outputStream.close();
}

void initializeNeuralNetwork(){
    NeuralNetworkOperator::initializeBiases("layer1Biases", 512);
    NeuralNetworkOperator::initializeBiases("layer2Biases", 256);
    NeuralNetworkOperator::initializeBiases("layer3Biases", 128);
    NeuralNetworkOperator::initializeBiases("layer4Biases", 64);
    NeuralNetworkOperator::initializeBiases("layer5Biases", 1);

    NeuralNetworkOperator::initializeWeightsRelu("layer1Weights", 768, 512);
    NeuralNetworkOperator::initializeWeightsRelu("layer2Weights", 512, 256);
    NeuralNetworkOperator::initializeWeightsRelu("layer3Weights", 256, 128);
    NeuralNetworkOperator::initializeWeightsRelu("layer4Weights", 128, 64);
    NeuralNetworkOperator::initializeWeightsSigmoid("layer5Weights", 64, 1);

}

float reluActivator(float value){
    if (value < 0) {return 0;}\
    else {return value;}
}

float sigmoidActivator(float value){
    return 1.0f / (1.0f + std::exp(-value));
}
 
float calculateSigmoidDelta(float predicted, float target){
    return 2 * (predicted - target) * predicted * (1 - predicted);
}
}




