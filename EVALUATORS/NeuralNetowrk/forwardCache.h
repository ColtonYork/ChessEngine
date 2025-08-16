#include <vector>


struct ForwardCache {
    std::vector<float> originalInput;    // 768 values (initial board state)
    std::vector<float> layer1Output;     // 512 values (after ReLU)
    std::vector<float> layer2Output;     // 256 values (after ReLU)
    std::vector<float> layer3Output;     // 128 values (after ReLU)
    std::vector<float> layer4Output;     // 64 values (after ReLU)

    std::vector<float> layer1PreActivation;
    std::vector<float> layer2PreActivation;
    std::vector<float> layer3PreActivation;
    std::vector<float> layer4PreActivation;

    std::vector<float> layer1Delta;
    std::vector<float> layer2Delta;
    std::vector<float> layer3Delta;
    std::vector<float> layer4Delta;
    std::vector<float> layer5Delta;


    float finalOutput = 0.0f;                  // 1 value (after sigmoid)
    float expectedOutput = 0.0f;



    
    // Constructor to pre-allocate memory
    ForwardCache() 
        {
            originalInput.resize(768);
            layer1Output.resize(512);
            layer2Output.resize(256);
            layer3Output.resize(128);
            layer4Output.resize(64);

            layer1PreActivation.resize(512);
            layer2PreActivation.resize(256);
            layer3PreActivation.resize(128);
            layer4PreActivation.resize(64);

            layer1Delta.resize(512);
            layer2Delta.resize(256);
            layer3Delta.resize(128);
            layer4Delta.resize(64);
            layer5Delta.resize(1);
        }
};