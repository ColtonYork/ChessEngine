#include "NeuralNetworkOperator.h"
#include "forwardCache.h"
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
   float forwardPass(const std::vector<float>& input);

    
    /*
        brief: computes a relu layer in the netwrok and returns the value of each neruons activation. (LAYER 1 means inputting the input tensor)

        forwardingLayer: The layer that will be forwarded in the network. input 1 means ~ 1 -> 2
    */
    void forwardLayerRelu(const std::vector<float>& input, const int& layerNum, const int& outputSize, ForwardCache& cache);


    /*
       brief: computes a sigmoid layer in the netwrok and returns the value of each neruons activation. (LAYER 1 means inputting the input tensor)

        forwardingLayer: The layer that will be forwarded in the network. input 1 means ~ 1 -> 2
    */
    void forwardLayerSigmoid(const std::vector<float>& input, ForwardCache& cache);


    /*
        Brief: loads the weight vectors with weights files
    */
    void loadWeightVector(const size_t& layerNum);


    /*
        Brief: Loads all 5 weight vectors with values from the 'weights' directory
    */
    void loadWeights();


    /*
        Brief: loads the bias vectors with weights files
    */
   void loadBiasVector(const size_t& layerNum);


   /*
        Brief: loads all weights vectors for the network based on the 'weights' files
   */
    void loadWeights();


    /*
        Brief: loads all Bias vectors for the network based on the 'weights' files
   */
  void loadBiases();


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

    std::vector<float> layer1Output;
    std::vector<float> layer2Output;
    std::vector<float> layer3Output;
    std::vector<float> layer4Output;
    std::vector<float> layer5Output;


    std::vector<ForwardCache> forwardCache;

    float finalOutput;
};