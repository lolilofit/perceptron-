#include <iostream>
#include "NeuronNetwork.h"
#include "CSVParser.h"

int main() {
    Data* data = new Data;

    CSVParser::readAndStoreData("dataset.csv", data);
    auto* network = new NeuronNetwork(data);
    network->build_initial_network("config.csv");
    for(int i = 0; i < 56; i++) {
        auto line = data->data[i];
        std::vector<float> right_answer;
        for (int k = 3; k >= 1; k--) {
            float val = data->data[i][data->totalColNum - 1 - k];
            right_answer.push_back(val);
        }
        std::vector<float> out = network->calk_output_vector(line);
        float error = network->calk_mistake(right_answer, out);
        std::cout << "Epoch - " << 0 << "; Error - " << error << "\n";
    }

    float total_error = 0.0;

    for(int i = 1; i < 27; i++) {
        for (int j = 0; j < 56; j++) {
            auto line = data->data[j];
            std::vector<float> right_answer;
            for(int k = 3; k >= 1; k--) {
                float val = data->data[j][data->totalColNum  - 1 - k];
                right_answer.push_back(val);
            }
            float error = network->train(right_answer, data->data[j], 0.1f);
            total_error += error;
            std::cout << "Epoch - " << i << "; Error - " << error << "\n";
        }
        std::cout << "Total Test Error: " << total_error/float(56.0f) << "\n";
        total_error = 0.0f;
        std::cout << "-----------\n";
    }

    float total_check_error = 0.0;

    for(int i = 56; i < data->data.size(); i++) {
        auto line = data->data[i];
        std::vector<float> right_answer;
        for (int k = 3; k >= 1; k--) {
            float val = data->data[i][data->totalColNum - 1 - k];
            right_answer.push_back(val);
        }
        std::vector<float> out = network->calk_output_vector(line);
        float error = network->calk_mistake(right_answer, out);
        total_check_error += error;
        std::cout << "\nCalculated mistake\n" << error;
    }

    std::cout << "\nTotal check error: " << total_check_error / (float)(data->data.size() - 56);
    return 0;
}
