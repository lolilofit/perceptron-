//
// Created by User on 09.03.2020.
//

#ifndef NEIRLAB3_HIDDENNEURON_H
#define NEIRLAB3_HIDDENNEURON_H

#include <map>
#include <vector>
#include "Neuron.h"

class HiddenNeuron : public Neuron {
private:
    std::vector<Edge*>* inputEdges;
public:
    HiddenNeuron();
    void calk_value();
    float calk_mistake(float target_val, float train_speed);
    float activation_function(float value);
    void push_input_edge(Edge* edge);
};


#endif //NEIRLAB3_HIDDENNEURON_H
