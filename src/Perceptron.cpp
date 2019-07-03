/**
 * This is a sandbox-network.
 * Its purpose is to let the programmer get accustomed with programming neural networks.
 * Some of the implementations might get copied to a general network-class later,
 * of which more specific networks can derive.
 */

#include <memory>

class SingleLayerPerceptron {
private:
    int _inputCount;
    float* _weights;
    float _bias = 0.0f;
    float _learningRate = 1.0f;
public:
    SingleLayerPerceptron(int inputCount) {
        _inputCount = inputCount;
        _weights = (float*)malloc(sizeof(float) * inputCount);
    }
    ~SingleLayerPerceptron() {
        free(_weights);
    }

    float passForward(float* p) {
        float sum = 0.0f; 
        for(int i=0; i<_inputCount; i++) {
            sum += _weights[i] * p[i];
        }
        sum += _bias;
        return sum;
    }
};

int main(int argc, char** argv) {
    SingleLayerPerceptron perceptron{2};
    
}