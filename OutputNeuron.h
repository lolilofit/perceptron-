//
// Created by User on 09.03.2020.
//

#ifndef NEIRLAB3_OUTPUTNEURON_H
#define NEIRLAB3_OUTPUTNEURON_H

#include <map>
#include <vector>
#include "Neuron.h"

class OutputNeuron : public Neuron {
private:
    std::vector<Edge*>* inputEdges;
    bool should_count = true;
public:
    OutputNeuron();
    void calk_value();
    float calk_mistake(float target_val, float train_speed);
    void push_input_edge(Edge* edge);
};


#endif //NEIRLAB3_OUTPUTNEURON_H
