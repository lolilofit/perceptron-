//
// Created by User on 09.03.2020.
//

#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <iostream>
#include "NeuronNetwork.h"
#include "Neuron.h"
#include "HiddenNeuron.h"
#include "OutputNeuron.h"

void NeuronNetwork::build_initial_network(const std::string& config_file_name) {
    std::ifstream config_input;
    config_input.open("..\\resources\\" + config_file_name);
    std::string line, token;
    getline(config_input, line);
    this->education_speed = std::stof(line);
    getline(config_input, line);
    int layers_num = std::stoi(line);
    int i = 0;

    std::vector<int> number_layers_neurons;
    for(int k = 0; k < layers_num; k++) {
        getline(config_input, line);
        number_layers_neurons.push_back(std::stoi(line));
    }
    config_input.close();

    auto* previous_layer =  new std::vector<Neuron*>();
    //!!!!!!!!!!!!!
    for(int j = 0; j < (this->data->totalColNum - 4); j++) {
    // for(int j = 0; j < (3); j++) {
        auto* inputNeuron = new Neuron();
        previous_layer->push_back(inputNeuron);
    }
    input_layer = previous_layer;


    auto* previous_hidden_layer =  new std::vector<HiddenNeuron*>();
    for(int j = 0; j < layers_num; j++) {
        auto* layer = new std::vector<HiddenNeuron*>();
        for(int k = 0; k < number_layers_neurons[j]; k++) {
            auto* neuron = new HiddenNeuron();

            if(j == 0) {
                for (int m = 0; m < previous_layer->size(); m++) {
                    auto el = (*previous_layer)[m];
                    Edge *edge = new Edge();
                    edge->set_a_nueron(el);
                    edge->set_b_nueron(neuron);
                    neuron->push_input_edge(edge);
                    el->push_output_edge(edge);
                }
            }
            else {
                for (int m = 0; m < previous_hidden_layer->size(); m++) {
                    auto el = (*previous_hidden_layer)[m];
                    Edge *edge = new Edge();
                    edge->set_a_nueron(el);
                    edge->set_b_nueron(neuron);
                    neuron->push_input_edge(edge);
                    el->push_output_edge(edge);
                }
            }
            layer->push_back(neuron);
        }
        this->all_layers.push_back(layer);
        previous_hidden_layer = layer;
        i++;
    }

    auto* outputLayer = new std::vector<OutputNeuron*>();
    for(int j = 0; j < 3; j++) {
        OutputNeuron* outputNeuron = new OutputNeuron();
        for(auto el : *previous_hidden_layer) {
            Edge* edge = new Edge();
            edge->set_a_nueron(el);
            edge->set_b_nueron(outputNeuron);
            outputNeuron->push_input_edge(edge);
            el->push_output_edge(edge);
        }
        outputLayer->push_back(outputNeuron);
    }
    this->output_layer = outputLayer;
}


NeuronNetwork::NeuronNetwork(Data *data) {
    this->data = data;
}

NeuronNetwork::~NeuronNetwork() {
    delete[](input_layer);
    delete[](output_layer);
    for(int i = 0; i < all_layers.size(); i++)
        delete[](all_layers[i]);
}

std::vector<float> NeuronNetwork::calk_output_vector(std::vector<float> &in) {
    std::vector<Neuron*>* currentLayer = input_layer;
    if(currentLayer->size() != (in.size() - 3))
        return std::vector<float>();

    for(int i = 0; i < currentLayer->size(); i++) {
        if(in[i] == std::numeric_limits<float>::infinity())
            (*currentLayer)[i]->set_should_count(false);
        else
            (*currentLayer)[i]->set_value(in[i]);
    }

    std::vector<HiddenNeuron*>* hidden_layer;
    for(int layer = 0; layer < all_layers.size(); layer++) {
        hidden_layer = all_layers[layer];
        for (int one_neuron_number = 0; one_neuron_number < hidden_layer->size(); one_neuron_number++) {
            HiddenNeuron* hiddenNeuron = (*hidden_layer)[one_neuron_number];
            hiddenNeuron->calk_value();
        }
    }
    //currentLayer = all_layers[all_layers.size() - 1];

    std::vector<OutputNeuron*>* output_layer = this->output_layer;
    std::vector<float> result;
    for (int one_neuron_number = 0; one_neuron_number < output_layer->size(); one_neuron_number++) {
        OutputNeuron* outputNeuron = (*output_layer)[one_neuron_number];
        //auto *outputNeuron = reinterpret_cast<OutputNeuron*>((*currentLayer)[one_neuron_number]);
        outputNeuron->calk_value();
        //(*currentLayer)[one_neuron_number]->calk_value();
        result.push_back(outputNeuron->get_value());
    }
    return result;
}

float NeuronNetwork::calk_mistake(std::vector<float> &rightanswer, std::vector<float> &result) {
//    std::vector<float> result = calk_output_vector(in);

    if(result.size() != rightanswer.size())
        throw std::exception();

    float error = 0.0;
    int el_num = 0;
    for(int i = 0; i < result.size(); i++) {
        if(result[i] != std::numeric_limits<float>::infinity() && rightanswer[i] != std::numeric_limits<float>::infinity()) {
            error += (float) std::pow((result[i] - rightanswer[i]), 2.0f);
            el_num++;
        }
    }
    return std::pow(error, 0.5f)/(float)el_num;
}

float NeuronNetwork::train(std::vector<float> &rightanswer, std::vector<float> &data, float epsilon) {

    for(int i = 0; i < rightanswer.size(); i++) {
        auto ans = rightanswer[i];
        OutputNeuron* neuron = (*this->output_layer)[i];
        neuron->set_should_count( true);
        if(ans == std::numeric_limits<float>::infinity())
            neuron->set_should_count(false);
    }

    std::vector<float> out = this->calk_output_vector(data);
    float error = calk_mistake(rightanswer, out);

   // while (error > epsilon) {
    //        std::cout << error << "\n";
        std::vector<OutputNeuron*>* layer = this->output_layer;
        for (int i = 0; i < layer->size(); i++) {
            auto *outputNeuron = (*layer)[i];
            float expec_val = 0.0;
            expec_val = rightanswer[i];
            outputNeuron->calk_mistake(expec_val, education_speed);
        }

        std::vector<HiddenNeuron*>* hidden_layer;
        for (int i = (all_layers.size() - 1); i >= 0; i--) {
            hidden_layer = all_layers[i];
            for (int j = 0; j < layer->size(); j++) {
                HiddenNeuron* neuron = (*hidden_layer)[j];
                neuron->calk_mistake(0.0f, education_speed);
            }
        }

        std::vector<Neuron*>* input_neurons = input_layer;
        for(int i = 0; i < input_neurons->size(); i++) {
            Neuron *neuron = (*input_neurons)[i];
            if(neuron->get_should_count()) {
                for (auto edge : *neuron->get_output_edges()) {
                    Neuron *a_neuron = edge->get_a_neuron();
                    Neuron *b_neuron = edge->get_b_neuron();

                    if (neuron != b_neuron) {
                        if (b_neuron->get_should_count()) {
                            float grad = neuron->get_value() * b_neuron->get_calculated_mistake();
                            edge->setWeigh(edge->getWeight() + education_speed * grad);
                        }
                    }
                    if (neuron != a_neuron) {
                        if (a_neuron->get_should_count()) {
                            float grad = neuron->get_value() * b_neuron->get_calculated_mistake();
                            edge->setWeigh(edge->getWeight() + education_speed * grad);
                        }
                    }
                    if ((neuron == a_neuron && neuron == b_neuron) || (neuron != a_neuron && neuron != b_neuron))
                        throw -1;
                }
            }
        }

        std::vector<float> pp = this->calk_output_vector(data);
        error = calk_mistake(rightanswer, pp);
        //std::cout << error << "\n";
        return error;
}

