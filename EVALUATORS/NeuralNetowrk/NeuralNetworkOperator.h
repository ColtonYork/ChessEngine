#include <string>
#include <vector>
#include "InputTensor.h"


namespace NeuralNetworkOperator{

    /*
        Brief: initializes the 768, 512, 256, 128, 64, 1 Neural network using the correct init methods

        THIS FUNCTION CAN OVERWRITE WEIGHTS
    */
   void initializeNeuralNetwork();


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


    /*
        Brief: takes in a number and converts it to its relu activation value

        value: the number being converted
    */
    float reluActivator(float value);


    /*
        Brief: takes in a number and converts it to its relu activation value

        value: the number being converted
    */
    float sigmoidActivator(float value);



    

}