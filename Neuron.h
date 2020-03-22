//
// Created by User on 09.03.2020.
//

#ifndef NEIRLAB3_NEURON_H
#define NEIRLAB3_NEURON_H

#include <list>
#include <vector>

class Neuron;

class Edge {
private:
    float weigh;
    float updated_weigh = 0.0;
    Neuron* a_neuron;
    Neuron* b_neuron;

public:
    Edge();
    void setWeigh(float val);
    float getWeight();
    Neuron* get_a_neuron();
    Neuron* get_b_neuron();
    void set_a_nueron(Neuron* neuron);
    void set_b_nueron(Neuron* neuron);
    float get_updated_weigh();
    void set_updated_weigh(float new_val);
};



//simple input neuron
class Neuron {
protected:
    float value;
    float calculated_mistake = 0.0;
    std::vector<Edge*>* outputEdges;
    bool should_count = true;
public:
    Neuron();

    float calk_mistake(float target_val,  float train_speed);
    void calk_value();
    void set_output_edges(std::vector<Edge*> *edges);
    std::vector<Edge*>* get_output_edges();
    std::vector<Edge*>* get_input_edges();
    void push_output_edge(Edge* edge);
    float get_value();
    void set_value(float value);

    bool get_should_count();
    void set_should_count(bool val);
    float get_calculated_mistake();
};

#endif //NEIRLAB3_NEURON_H
