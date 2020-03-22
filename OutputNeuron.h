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
  //  float resultValue = 0.0;
    std::vector<Edge*>* inputEdges;
    bool should_count = true;
public:
    OutputNeuron();
    void setInputEdges(std::vector<Edge*>* inputEdges);
    void calk_value();
    float calk_mistake(float target_val, float train_speed);
  //  void set_result_value(float value);
 //   float get_result_value();
    std::vector<Edge*>* get_input_edges();
    void push_input_edge(Edge* edge);
};


#endif //NEIRLAB3_OUTPUTNEURON_H
