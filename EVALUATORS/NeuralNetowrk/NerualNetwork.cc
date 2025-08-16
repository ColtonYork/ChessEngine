#include "NeuralNetwork.h"
#include <fstream>
#include <iostream>


NeuralNetwork::NeuralNetwork(){
    layer1Weights.resize(393216);     // 768 * 512
    layer2Weights.resize(131072);     // 512 * 256
    layer3Weights.resize(32768);      // 512 * 256
    layer4Weights.resize(8192);       // 128 * 64
    layer5Weights.resize(64);         // 64 * 1

    layer1Biases.resize(512);
    layer2Biases.resize(256);
    layer3Biases.resize(128);
    layer4Biases.resize(64);
    layer5Biases.resize(1);

    layer1Output.resize(512);
    layer2Output.resize(256);
    layer3Output.resize(128);
    layer4Output.resize(64);
    layer5Output.resize(1);

    layer1WeightGrad.resize(512 * 768);
    layer2WeightGrad.resize(256 * 512);
    layer3WeightGrad.resize(128 * 256);
    layer4WeightGrad.resize(64 * 128);
    layer5WeightGrad.resize(1 * 64);

    layer1BiasGrad.resize(512);
    layer2BiasGrad.resize(256);
    layer3BiasGrad.resize(128);
    layer4BiasGrad.resize(64);
    layer5BiasGrad.resize(1);

    forwardCache.resize(64);

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

void NeuralNetwork::forwardLayerRelu(const std::vector<float>& input, const int& layerNum, const int& outputSize, ForwardCache& cache){    
    std::vector<float>* weights;
    std::vector<float>* biases;
    std::vector<float>* outputVec;
    std::vector<float>* preActivationVec;

    switch (layerNum)
        {
            case 1: 
                {
                    weights = &layer1Weights;
                    biases = &layer1Biases;
                    outputVec = &layer1Output; 
                    preActivationVec = &cache.layer1PreActivation;
                    break;
                }
            case 2: 
                {
                    weights = &layer2Weights;
                    biases = &layer2Biases;
                    outputVec = &layer2Output; 
                    preActivationVec = &cache.layer2PreActivation;

                    break;

                }
            case 3: 
                {
                    weights = &layer3Weights;
                    biases = &layer3Biases;
                    outputVec = &layer3Output;
                    preActivationVec = &cache.layer3PreActivation;
 
                    break;
                }
            case 4: 
                {
                    weights = &layer4Weights;
                    biases = &layer4Biases;
                    outputVec = &layer4Output; 
                    preActivationVec = &cache.layer4PreActivation;

                    break;
                }
            default: std::cout << "[7][DEBUG][NeuralNetwork::forwardLayerRelu]\n"; return;


        }

        for(int outputNeuron = 0; outputNeuron < outputSize; outputNeuron++)
            {
                int nextNeuronStart = outputNeuron * input.size();
                float sum = 0.0f;
                for(int k = 0; k < input.size(); k++)
                    {
                        sum += input[k] * (*weights)[nextNeuronStart + k];  // ->at(nextNeuronStart + k)
                    }
                sum += (*biases)[outputNeuron];

                //set the preactivation vector in the cache
                (*preActivationVec)[outputNeuron] = sum;

                //RELU
                if (sum < 0) {sum = 0;}
                (*outputVec)[outputNeuron] = sum;
            }
        return;
}

void NeuralNetwork::forwardLayerSigmoid(const std::vector<float>& input, ForwardCache& cache){
    float sum = 0.0f;

    std::vector<float>* weights = &layer5Weights;
    std::vector<float>* biases = &layer5Biases;
    std::vector<float>* outputVec = &layer5Output;




    // forwarding sigmoid only needed for final output neuron AKA layer5weighs/biases
    for (int i = 0; i < input.size(); i++)
        {
            sum += input[i] * (*weights)[i];
        }
        sum += (*biases)[0];

        float sigmoid = NeuralNetworkOperator::sigmoidActivator(sum);
        (*outputVec)[0] = sigmoid;
        finalOutput = sigmoid;
        cache.finalOutput = finalOutput;
        return;
}

float NeuralNetwork::forwardPass(const std::vector<float>& input){
    
    ForwardCache cache;
    forwardLayerRelu(input, 1, 512, cache);
    cache.originalInput = input;

    forwardLayerRelu(layer1Output, 2, 256, cache);
    cache.layer1Output = layer1Output;

    forwardLayerRelu(layer2Output, 3, 128, cache);
    cache.layer2Output = layer2Output;

    forwardLayerRelu(layer3Output, 4, 64, cache);
    cache.layer3Output = layer3Output;

    forwardLayerSigmoid(layer4Output, cache);
    cache.layer4Output = layer4Output;

    cache.finalOutput = finalOutput;

    forwardCache.push_back(cache);

    return finalOutput;

}

void NeuralNetwork::backpropogateSigmoidLayer(ForwardCache& cache){
    float delta = NeuralNetworkOperator::calculateSigmoidDelta(cache.finalOutput, cache.expectedOutput);

    std::vector<float>* weightGrad = &layer5WeightGrad;
    std::vector<float>* biasGrad = &layer5BiasGrad;
    std::vector<float>* previousOutput = &cache.layer4Output;
    

    for (size_t i = 0; i < weightGrad->size(); i++)
        {
            (*weightGrad)[i] += delta * (*previousOutput)[i];
        }

        (*biasGrad)[0] += delta;
        cache.layer5Delta[0] = delta;
}

void NeuralNetwork::backpropogateReluLayer(ForwardCache& cache, const int& layerNum){

    if (layerNum > 4 || layerNum < 1) {std::cout << "[0][DEBUG][NeuralNetwork::backpropogateReluLayer]\n"; return;}

    std::vector<float>* weightGrad = nullptr;
    std::vector<float>* nextLayerWeights = nullptr;
    std::vector<float>* biasGrad = nullptr;
    std::vector<float>* preActivations = nullptr;
    std::vector<float>* lastOutput = nullptr;
    std::vector<float>* nextDeltas = nullptr;
    std::vector<float>* deltas = nullptr;

    switch (layerNum)
        {
            case 1: weightGrad = &layer1WeightGrad; biasGrad = &layer1BiasGrad; nextLayerWeights = &layer2Weights; lastOutput = &cache.originalInput; preActivations = &cache.layer1PreActivation; nextDeltas = &cache.layer2Delta; deltas = &cache.layer1Delta; break;
            case 2: weightGrad = &layer2WeightGrad; biasGrad = &layer2BiasGrad; nextLayerWeights = &layer3Weights; lastOutput = &cache.layer1Output; preActivations = &cache.layer2PreActivation; nextDeltas = &cache.layer3Delta; deltas = &cache.layer2Delta; break;
            case 3: weightGrad = &layer3WeightGrad; biasGrad = &layer3BiasGrad; nextLayerWeights = &layer4Weights; lastOutput = &cache.layer2Output; preActivations = &cache.layer3PreActivation; nextDeltas = &cache.layer4Delta; deltas = &cache.layer3Delta; break;
            case 4: weightGrad = &layer4WeightGrad; biasGrad = &layer4BiasGrad; nextLayerWeights = &layer5Weights; lastOutput = &cache.layer3Output; preActivations = &cache.layer4PreActivation; nextDeltas = &cache.layer5Delta; deltas = &cache.layer4Delta; break;
        }

    
        for (size_t i = 0; i < biasGrad->size(); i++)
            {

                //caclulate weights for next layer for the neruon to find delta
                std::vector<float> weightsForNextNeuron(nextDeltas->size());
                for (size_t k = 0; k < nextDeltas->size(); k++)
                    {
                        weightsForNextNeuron[k] = (*nextLayerWeights)[k * biasGrad->size() + i];
                    }


                float delta = NeuralNetworkOperator::calculateReLUDelta(*nextDeltas, weightsForNextNeuron, (*preActivations)[i] );
                (*deltas)[i] = delta;
                for (size_t j = 0; j < lastOutput->size(); j++)
                    {
                        unsigned int weightIndex = i * lastOutput->size() + j;

                        (*weightGrad)[weightIndex] += delta * (*lastOutput)[j];

                    }
                    (*biasGrad)[i] += delta;
            }

}

void NeuralNetwork::backpropogate(){
    std::fill(layer1WeightGrad.begin(), layer1WeightGrad.end(), 0.0f);
    std::fill(layer2WeightGrad.begin(), layer2WeightGrad.end(), 0.0f);
    std::fill(layer3WeightGrad.begin(), layer3WeightGrad.end(), 0.0f);
    std::fill(layer4WeightGrad.begin(), layer4WeightGrad.end(), 0.0f);
    std::fill(layer5WeightGrad.begin(), layer5WeightGrad.end(), 0.0f);

    std::fill(layer1BiasGrad.begin(), layer1BiasGrad.end(), 0.0f);
    std::fill(layer2BiasGrad.begin(), layer2BiasGrad.end(), 0.0f);
    std::fill(layer3BiasGrad.begin(), layer3BiasGrad.end(), 0.0f);
    std::fill(layer4BiasGrad.begin(), layer4BiasGrad.end(), 0.0f);
    std::fill(layer5BiasGrad.begin(), layer5BiasGrad.end(), 0.0f);

    for(int i = 0; i < forwardCache.size(); i++)
        {
            ForwardCache* currentCache = &forwardCache[i];

            backpropogateSigmoidLayer(*currentCache);

            backpropogateReluLayer(*currentCache, 4);
            backpropogateReluLayer(*currentCache, 3);
            backpropogateReluLayer(*currentCache, 2);
            backpropogateReluLayer(*currentCache, 1);
        }

    updateWeights(forwardCache.size());
    updateBiases(forwardCache.size());
}

void NeuralNetwork::updateWeights(size_t batchSize){
    for (size_t i = 0; i < layer1WeightGrad.size(); i++){layer1Weights[i] -= (LEARNING_RATE / batchSize) * layer1WeightGrad[i];}
    for (size_t i = 0; i < layer2WeightGrad.size(); i++){layer2Weights[i] -= (LEARNING_RATE / batchSize) * layer2WeightGrad[i];}
    for (size_t i = 0; i < layer3WeightGrad.size(); i++){layer3Weights[i] -= (LEARNING_RATE / batchSize) * layer3WeightGrad[i];}
    for (size_t i = 0; i < layer4WeightGrad.size(); i++){layer4Weights[i] -= (LEARNING_RATE / batchSize) * layer4WeightGrad[i];}
    for (size_t i = 0; i < layer5WeightGrad.size(); i++){layer5Weights[i] -= (LEARNING_RATE / batchSize) * layer5WeightGrad[i];}
}

void NeuralNetwork::updateBiases(size_t batchSize){
    for (size_t i = 0; i < layer1BiasGrad.size(); i++){layer1Biases[i] -= (LEARNING_RATE / batchSize) * layer1BiasGrad[i];}
    for (size_t i = 0; i < layer2BiasGrad.size(); i++){layer2Biases[i] -= (LEARNING_RATE / batchSize) * layer2BiasGrad[i];}
    for (size_t i = 0; i < layer3BiasGrad.size(); i++){layer3Biases[i] -= (LEARNING_RATE / batchSize) * layer3BiasGrad[i];}
    for (size_t i = 0; i < layer4BiasGrad.size(); i++){layer4Biases[i] -= (LEARNING_RATE / batchSize) * layer4BiasGrad[i];}
    for (size_t i = 0; i < layer5BiasGrad.size(); i++){layer5Biases[i] -= (LEARNING_RATE / batchSize) * layer5BiasGrad[i];}
}





