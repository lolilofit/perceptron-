//
// Created by User on 09.03.2020.
//

#include <vector>
#include "Neuron.h"


void Neuron::set_output_edges(std::vector<Edge *> *edges) {
        outputEdges = edges;
}

float Neuron::get_value() {
    return value;
}

void Neuron::set_value(float value) {
    this->value = value;
}

void Neuron::push_output_edge(Edge *edge) {
    outputEdges->push_back(edge);
}

std::vector<Edge *> *Neuron::get_output_edges() {
    return outputEdges;
}

Neuron::Neuron() {
    outputEdges = new std::vector<Edge*>();
}

void Neuron::calk_value() {}

std::vector<Edge *> *Neuron::get_input_edges() {
    return nullptr;
}

float Neuron::calk_mistake(float target_val, float train_speed) {
    return 0.0;
}

void Neuron::set_should_count(bool val) {
    this->should_count = val;
}

bool Neuron::get_should_count() {
    return this->should_count;
}

float Neuron::get_calculated_mistake() {
    return calculated_mistake;
}





