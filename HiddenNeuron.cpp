//
// Created by User on 09.03.2020.
//

#include <cmath>
#include <iostream>
#include <limits>
#include "HiddenNeuron.h"

float HiddenNeuron::activation_function(float value) {

    //return (float)(value >= activation_step);
    float exp_val = std::exp((-1.0f)*value);
    if(exp_val == std::numeric_limits<float>::infinity())
        throw -1;
    float ret_val = 1.0f/(1.0f + exp_val);
    return ret_val;

}

void HiddenNeuron::calk_value() {
    float total_sum = 0.0;
    for(auto edge : *inputEdges) {
        Neuron* a_neuron = edge->get_a_neuron();
        Neuron* b_neuron = edge->get_b_neuron();
        if(this != a_neuron) {
            if(a_neuron->get_value() != std::numeric_limits<float>::infinity())
                total_sum += edge->getWeight() * a_neuron->get_value();
            else {
                std::cout << "inf\n";
            }
        }
        if(this != b_neuron) {
            if(b_neuron->get_value() != std::numeric_limits<float>::infinity())
                total_sum += edge->getWeight() * b_neuron->get_value();
            else {
                std::cout << "inf\n";
            }
        }
        if((this == a_neuron && this == b_neuron) || (this != a_neuron && this != b_neuron))
            throw -1;
    }
    float value = activation_function(total_sum);
    this->set_value(value);
}

//????????
//param - то, что должно быть на выходе
float HiddenNeuron::calk_mistake(float target_val, float train_speed) {
    float summ = 0.0;
    for(auto edge : *outputEdges) {
        Neuron* a_neuron = edge->get_a_neuron();
        Neuron* b_neuron = edge->get_b_neuron();

        if(this != b_neuron) {
            if(b_neuron->get_should_count())
                summ += b_neuron->get_calculated_mistake() * edge->getWeight();
        }
        if(this != a_neuron) {
            if(a_neuron->get_should_count())
                summ += a_neuron->get_calculated_mistake() * edge->getWeight();
        }
        if((this == a_neuron && this == b_neuron) || (this != a_neuron && this != b_neuron))
            throw -1;
    }
    float val = get_value()*(1.0f - get_value())*summ;
    this->calculated_mistake = val;

    for(auto edge : *outputEdges) {
        Neuron* a_neuron = edge->get_a_neuron();
        Neuron* b_neuron = edge->get_b_neuron();

        if(this != b_neuron) {
            if(b_neuron->get_should_count()) {
                float grad = this->get_value()*b_neuron->get_calculated_mistake();
                edge->setWeigh(edge->getWeight() + train_speed*grad);
            }
        }
        if(this != a_neuron) {
            if(a_neuron->get_should_count()) {
                float grad = this->get_value()*a_neuron->get_calculated_mistake();
                edge->setWeigh(edge->getWeight() + train_speed*grad);
            }
        }
        if((this == a_neuron && this == b_neuron) || (this != a_neuron && this != b_neuron))
            throw -1;

    }
    return val;
}

void HiddenNeuron::set_input_edges(std::vector<Edge *> *inputEdges) {
    this->inputEdges = inputEdges;
}


HiddenNeuron::HiddenNeuron() : Neuron() {
    //this->activation_step = activation_step;
    inputEdges = new std::vector<Edge*>();
}

void HiddenNeuron::push_input_edge(Edge *edge) {
    inputEdges->push_back(edge);
}

std::vector<Edge *> *HiddenNeuron::get_input_edges() {
    return inputEdges;
}

