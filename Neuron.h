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
    std::vector<Edge*>* get_output_edges();
    void push_output_edge(Edge* edge);
    float get_value();
    void set_value(float value);
    bool get_should_count();
    void set_should_count(bool val);
    float get_calculated_mistake();
};

#endif //NEIRLAB3_NEURON_H
