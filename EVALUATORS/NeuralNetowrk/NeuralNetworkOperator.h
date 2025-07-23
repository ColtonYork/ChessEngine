#include <string>
#include "InputTensor.h"


namespace NeuralNetworkOperator{

    /*
        Brief: Taked in a 768 neuron input tensor and forward passes thru a 512, 256, 128, 64 hidden layer then to a single output between 0 and 1. Closer to 1 means that white is winning

        input: The input board tensor that will be evaluated
    */
    float forwardPass(const InputTensor& input);


    /*
        Brief: resets all biases in a given file to 0
    */
    void initializeBiases(const std::string& fileName, size_t numBiases);


    /*
        Brief: Initilizes weights in a specified file using He initilization. Weights will mostly be initilized form +-0.15

        fileName: The file to input these wieghts into
        numWeights: The numbers of weights that need to be initialized
    */
   void initializeWeightsRelu(const std::string& fileName, size_t inputNeurons, size_t outputNeurons);

    /*
        Brief: initiliaizes weights in a specified file using Xavier initilization. Weights will be mostly initialized from +-0.304
       
        fileName: The file to input these wieghts into
        numWeights: The numbers of weights that need to be initialized
    */
    void initializeWeightsSigmoid(const std::string& fileName, size_t inputNeurons,  size_t outputNeurons);

    

}