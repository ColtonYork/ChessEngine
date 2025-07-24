#include "NeuralNetwok.h"
#include <fstream>
#include <iostream>


NeuralNetwork::NeuralNetwork(){

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
    //l1W
    std::ifstream inputStream;
    inputStream.open("weights/layer1Weights");
    if (!inputStream.is_open()) {std::cout << "[0][DEBUG][NerualNetwork::NeuralNetwork]\n"; return;}




}
