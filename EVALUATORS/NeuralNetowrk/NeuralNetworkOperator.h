#include <string>
#include <vector>


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

    
    /*
        Brief: calculates the delta for hte output sigmoid

        Predicted: The value that the netwrok predicted
        Target: the target value for the training run
    */
    float calculateSigmoidDelta(float predicted, float target);

    /*
        Brief: calculates the delta of a hidden layer neuron and returns it

        nextDeltas: The deltas of the nect layer
        nextWeightsForNeuron: The weights for the next layer in order to calulate delta for the current neuron
        preActivation: the pre activation value of the current neuron
    */
    float calculateReLUDelta(const std::vector<float>& nextDeltas, const std::vector<float>& nextWeightsForNeuron, float preActivation);


}

