#include <memory>

class Layer {
private:
    int _inputCount;
    int _outputCount;
    float* _outputs;
    float* _biases;
    float** _weights;
public:
    /**
     * Constructors and Destructors
     */
    Layer() {}
    Layer(int inputCount, int outputCount) {
        _inputCount = inputCount;
        _outputCount = outputCount;

        /*
            allocate memory for weights, biases and outputs 
        */
        _outputs = (float*)malloc(sizeof(float) * outputCount);
        _biases = (float*)malloc(sizeof(float) * outputCount);
        _weights = (float**)malloc(sizeof(float*) * outputCount);
        for(int i=0; i<outputCount; i++) {
            _weights[i] = (float*)malloc(sizeof(float) * inputCount);
        }
    }
    ~Layer() {
        for(int i=0; i<_outputCount; i++) { free(_weights[i]); }
        free(_weights);
        free(_biases);
        free(_outputs);
    }


    /**
     * public methods
     */

    /*
        Calculates and returns a network-output
    */
    float* calcOutput(float* inputs) {
        for(int i=0; i<_outputCount; i++) {
            float subSum = 0;
            float* subWeights = _weights[i];

            for(int j=0; j<_inputCount; j++) { subSum += subWeights[j] * inputs[j]; }
            subSum += _biases[i];

            if(subSum < 0) subSum = 0;
            else subSum = 1;
            _outputs[i] = subSum;
        }
        return _outputs;
    }
private:
    /**
     * private methods
     */
};

class MultiLayerPerceptron {
private:
    int _inputCount;
    int _layerCount;
    Layer** _layers;
    float _error;
    float _learningRate;
public:
    MultiLayerPerceptron() {}
    MultiLayerPerceptron(int layerCount, int* layerInputCounts) {
        _layerCount = layerCount;

        /*
            allocate memory for layers
            and their input-counts
            instantiate layers
        */
        _layers = (Layer**)malloc(sizeof(Layer*) * layerCount);
        for(int i=0; i<layerCount-1; i++) {
            _layers[i] = new Layer(layerInputCounts[i], layerInputCounts[i+1]);
        }
        _layers[layerCount-1] = new Layer(layerInputCounts[layerCount-1], 1);
    }
    ~MultiLayerPerceptron() {
        for(int i=0; i<_layerCount; i++) { delete _layers[i]; }
        free(_layers);
    }
    float forwardPass(float* inputs, float target) {
        for(int i=0; i<_layerCount-1; i++) {
            inputs = _layers[i]->calcOutput(inputs);
        }
        float output = _layers[_layerCount-1]->calcOutput(inputs)[0];
        _error = target - output;
        return output;
    }
};





int main(int argc, char** argv) {
    MultiLayerPerceptron network = MultiLayerPerceptron{};


    return 0;
}