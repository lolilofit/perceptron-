#include <iostream>
#include "NeuronNetwork.h"
#include "CSVParser.h"

int main() {
    Data* data = new Data;

    CSVParser::readAndStoreData("dataset.csv", data);
    auto* network = new NeuronNetwork(data);
    network->build_initial_network("config.csv");

    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 56; j++) {
            auto line = data->data[j];
            std::vector<float> right_answer;
            for(int k = 3; k >= 1; k--) {
                float val = data->data[j][data->totalColNum  - 1 - k];
                right_answer.push_back(val);
            }
            network->train(right_answer, data->data[j], 0.1f);
            std::cout << "-----------\n";
        }
    }

    for(int i = 58; i < 93; i++) {
        auto line = data->data[i];
        std::vector<float> right_answer;
        for (int k = 3; k >= 1; k--) {
            float val = data->data[i][data->totalColNum - 1 - k];
            right_answer.push_back(val);
        }
        std::vector<float> out = network->calk_output_vector(line);
        float error = network->calk_mistake(right_answer, out);
        std::cout << "\nCalculated mistake\n" << error;
    }

    return 0;
}
