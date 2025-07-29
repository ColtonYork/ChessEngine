#include "NeuralNetwok.h"
#include <fstream>
#include <iostream>


NeuralNetwork::NeuralNetwork(){
    layer1Weights.resize(393216); // [768][512]

    layer1Weights.resize(393216);
    layer2Weights.resize(131072);
    layer3Weights.resize(32768);
    layer4Weights.resize(8192);
    layer5Weights.resize(64);

    layer1Biases.resize(512);
    layer2Biases.resize(256);
    layer3Biases.resize(128);
    layer4Biases.resize(64);
    layer5Biases.resize(1);

    loadWeights();
    loadBiases();
}

void NeuralNetwork::loadWeightVector(const size_t& layerNum){
    if (layerNum > 5 || layerNum < 1) {std::cout << "[0][DEBUG][NeuralNetwork::loadWeightsVector]\n"; return;}

    std::ifstream inputStream;

    switch (layerNum)   
        {
            case 1: 
                {
                    inputStream.open("weights/layer1Weights");
                    if (!inputStream.is_open()) {std::cout << "[1][DEBUG][NeuralNetwork::loadWeightVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer1Weights.size();)
                        {
                            layer1Weights[i] = loadFloat;
                            i++;
                        }
            
                 if (i != layer1Weights.size()) {std::cout << "layer1Weights Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
            }

            case 2: 
                {
                    inputStream.open("weights/layer2Weights");
                    if (!inputStream.is_open()) {std::cout << "[2][DEBUG][NeuralNetwork::loadWeightVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer2Weights.size();)
                        {
                            layer2Weights[i] = loadFloat;
                            i++;
                        }
            
                    if (i != layer2Weights.size()) {std::cout << "layer2Weights Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }
                
            case 3: 
                {
                    inputStream.open("weights/layer3Weights");
                    if (!inputStream.is_open()) {std::cout << "[3][DEBUG][NeuralNetwork::loadWeightVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer3Weights.size();)
                        {
                            layer3Weights[i] = loadFloat;
                            i++;
                        }
            
                    if (i != layer3Weights.size()) {std::cout << "layer3Weights Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }

            case 4: 
                {
                    inputStream.open("weights/layer4Weights");
                    if (!inputStream.is_open()) {std::cout << "[4][DEBUG][NeuralNetwork::loadWeightVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer4Weights.size();)
                        {
                            layer4Weights[i] = loadFloat;
                            i++;
                        }
            
                    if (i != layer4Weights.size()) {std::cout << "layer4Weights Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }

            case 5: 
                {
                    inputStream.open("weights/layer5Weights");
                    if (!inputStream.is_open()) {std::cout << "[5][DEBUG][NeuralNetwork::loadWeightVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer5Weights.size();)
                        {
                            layer5Weights[i] = loadFloat;
                            i++;
                        }
            
                    if (i != layer5Weights.size()) {std::cout << "layer5Weights Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }
            default: std::cout << "[6][DEBUG][NeuralNetwork::loadWeightVector]\n"; return;
        }
        return;
}

void NeuralNetwork::loadBiasVector(const size_t& layerNum){
    if (layerNum > 5 || layerNum < 1) {std::cout << "[0][DEBUG][NeuralNetwork::loadWeights]\n"; return;}

    std::ifstream inputStream;

    switch (layerNum)   
        {
            case 1: 
                {
                    inputStream.open("biases/layer1Biases");
                    if (!inputStream.is_open()) {std::cout << "[1][DEBUG][NerualNetwork::loadBiasVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer1Biases.size();)
                        {
                            layer1Biases[i] = loadFloat;
                            i++;
                        }
            
                 if (i != layer1Biases.size()) {std::cout << "layer1Biases Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }

            case 2: 
                {
                    inputStream.open("biases/layer2Biases");
                    if (!inputStream.is_open()) {std::cout << "[2][DEBUG][NerualNetwork::loadBiasVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer2Biases.size();)
                        {
                            layer2Biases[i] = loadFloat;
                            i++;
                        }
            
                 if (i != layer2Biases.size()) {std::cout << "layer2Biases Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }

            case 3: 
                {
                    inputStream.open("biases/layer3Biases");
                    if (!inputStream.is_open()) {std::cout << "[3][DEBUG][NerualNetwork::loadBiasVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer3Biases.size();)
                        {
                            layer3Biases[i] = loadFloat;
                            i++;
                        }
            
                 if (i != layer3Biases.size()) {std::cout << "layer3Biases Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }

            case 4: 
                {
                    inputStream.open("biases/layer4Biases");
                    if (!inputStream.is_open()) {std::cout << "[4][DEBUG][NerualNetwork::loadBiasVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer4Biases.size();)
                        {
                            layer4Biases[i] = loadFloat;
                            i++;
                        }
            
                 if (i != layer4Biases.size()) {std::cout << "layer4Biases Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }

            case 5: 
                {
                    inputStream.open("biases/layer5Biases");
                    if (!inputStream.is_open()) {std::cout << "[5][DEBUG][NerualNetwork::loadBiasVector]\n"; return;}
        
                    float loadFloat;
                    int i = 0;
        
                    while (inputStream >> loadFloat && i < layer5Biases.size();)
                        {
                            layer5Biases[i] = loadFloat;
                            i++;
                        }
            
                 if (i != layer5Biases.size()) {std::cout << "layer5Biases Loaded Incorectly\n"; return;}
        
                    inputStream.close();
                    return;
                }
                default: std::cout << "[6][DEBUG][NeuralNetwork::loadBiasVector]\n"; return;
        }
        return;
}

void NeuralNetwork::loadWeights(){
    loadWeightVector(1);
    loadWeightVector(2);
    loadWeightVector(3);
    loadWeightVector(4);
    loadWeightVector(5);
}

void NeuralNetwork::loadBiases(){

    loadBiasVector(1);
    loadBiasVector(2);
    loadBiasVector(3);
    loadBiasVector(4);
    loadBiasVector(5);
}

std::vector<float> NeuralNetwork::forwardLayerRelu(const std::vector<float>& input, const int& layerNum, const int& outputSize){
    std::vector<float> returnVec(outputSize);
    
    std::vector<float>* weights;
    std::vector<float>* biases;

    switch (layerNum)
        {
            case 1: 
                {
                    weights = &layer1Weights;
                    biases = &layer1Biases;
                    break;
                }
            case 2: 
                {
                    weights = &layer2Weights;
                    biases = &layer2Biases;
                    break;

                }
            case 3: 
                {
                    weights = &layer3Weights;
                    biases = &layer3Biases;
                    break;
                }
            case 4: 
                {
                    weights = &layer4Weights;
                    biases = &layer4Biases;
                    break;
                }
            case 5: 
                {
                    weights = &layer5Weights;
                    biases = &layer5Biases;
                    break;
                }
        }

        for(int outputNeuron = 0; outputNeuron < outputSize; outputNeuron++)
            {
                int nextNeuronStart = outputNeuron * input.size();
                float sum = 0.0f;
                for(int k = 0; k < input.size(); k++)
                    {
                        sum += input.at(k) * weights->at(nextNeuronStart + k);
                    }
                sum += biases->at(outputNeuron);

                //RELU
                if (sum < 0) {sum = 0;}
                returnVec.at(outputNeuron) = sum;
            }
        return returnVec;
}

float NeuralNetwork::forwardPass(const InputTensor& input){
    
}
