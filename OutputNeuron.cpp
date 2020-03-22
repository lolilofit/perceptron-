//
// Created by User on 09.03.2020.
//

#include <cmath>
#include <iostream>
#include "OutputNeuron.h"

void OutputNeuron::calk_value() {
    if(!this->get_should_count()) {
        this->set_value(1.0f/0.0);
        return;
    }
    float total_sum = 0.0;
    for(auto edge : *inputEdges) {
        Neuron* a_neuron = edge->get_a_neuron();
        Neuron* b_neuron = edge->get_b_neuron();
        if(this != a_neuron)
            total_sum += edge->getWeight() * a_neuron->get_value();
        if(this != b_neuron)
            total_sum += edge->getWeight() * b_neuron->get_value();
        if((this == a_neuron && this == b_neuron) || (this != a_neuron && this != b_neuron))
            throw -1;
    }
    this->set_value(total_sum);
}

//void OutputNeuron::set_result_value(float value) {
//    this->resultValue = value;
//}

//float OutputNeuron::get_result_value() {
//    return this->resultValue;
//}

float OutputNeuron::calk_mistake(float target_val, float train_speed) {
    float val = (target_val - this->get_value());
    this->calculated_mistake = val;
    //float correction = (-1.0f)*neigh_val*train_speed*val;
    //related_edge->set_updated_weigh(related_edge->getWeight() + correction);
    return val;
}

void OutputNeuron::setInputEdges(std::vector<Edge*>* edges) {
    this->inputEdges = edges;
}

OutputNeuron::OutputNeuron() : Neuron() {
    this->inputEdges = new std::vector<Edge*>();
    this->outputEdges->clear();
}

void OutputNeuron::push_input_edge(Edge *edge) {
    inputEdges->push_back(edge);
}

std::vector<Edge *> *OutputNeuron::get_input_edges() {
    return  inputEdges;
}



