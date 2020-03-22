//
// Created by User on 13.03.2020.
//

#include "Neuron.h"

Edge::Edge() {
        weigh = 0.01f;
        a_neuron = nullptr;
        b_neuron = nullptr;
}

void Edge::setWeigh(float val) {
    weigh = val;
}

float Edge::getWeight() {
    return weigh;
}

Neuron *Edge::get_a_neuron() {
    return a_neuron;
}

Neuron *Edge::get_b_neuron() {
    return b_neuron;
}

void Edge::set_a_nueron(Neuron *neuron) {
    a_neuron = neuron;
}

void Edge::set_b_nueron(Neuron *neuron) {
    b_neuron = neuron;
}



