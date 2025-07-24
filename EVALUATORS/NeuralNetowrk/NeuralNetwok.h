#include "NeuralNetworkOperator.h"
#include <vector>


class NeuralNetwork{
    public:
    
    /*
        Brief: creates a neural netowrk and loads the vectors witht he current weight/bias values that are stored
    */
    NeuralNetwork();

    /*
        Brief: Taked in a 768 neuron input tensor and forward passes thru a 512, 256, 128, 64 hidden layer then to a single output between 0 and 1. Closer to 1 means that white is winning

        input: The input board tensor that will be evaluated
    */
   float forwardPass(const InputTensor& input);

    
    /*
        brief: computes a relu layer in the netwrok and returns the value of each neruons activation
    */
   std::vector<float> forwardLayerRelu(size_t outputSize);


    /*
       brief: computes a sigmoid layer in the netwrok and returns the value of each neruons activation
    */
  std::vector<float> forwardLayerSigmoid();


    private:
    std::vector<float> layer1Weights;
    std::vector<float> layer2Weights;
    std::vector<float> layer3Weights;
    std::vector<float> layer4Weights;
    std::vector<float> layer5Weights;

    std::vector<float> layer1Biases;
    std::vector<float> layer2Biases;
    std::vector<float> layer3Biases;
    std::vector<float> layer4Biases;
    std::vector<float> layer5Biases;



};