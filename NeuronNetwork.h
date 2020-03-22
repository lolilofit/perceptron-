//
// Created by User on 09.03.2020.
//

#ifndef NEIRLAB3_NEURONNETWORK_H
#define NEIRLAB3_NEURONNETWORK_H


#include <string>
#include <list>
#include "Neuron.h"
#include "Data.h"
#include "HiddenNeuron.h"
#include "OutputNeuron.h"

class NeuronNetwork {
private:
    std::vector<Neuron*>* input_layer;
    std::vector<OutputNeuron*>* output_layer;
    std::vector<std::vector<HiddenNeuron*>*> all_layers;

    //education speed
    float education_speed;
    Data* data;
public:
    NeuronNetwork(Data* data);
    ~NeuronNetwork();
    void build_initial_network(const std::string& config_file_name);
    std::vector<float> calk_output_vector(std::vector<float> &in);
    float calk_mistake(std::vector<float> &rightanswer, std::vector<float> &result);
    void train(std::vector<float> &rightanswer, std::vector<float> &data, float epsilon);
};

#endif //NEIRLAB3_NEURONNETWORK_H
