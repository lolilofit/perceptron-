cmake_minimum_required(VERSION 3.15)
project(NeirLab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(NeirLab3 main.cpp CSVParser.cpp Neuron.cpp HiddenNeuron.cpp OutputNeuron.cpp NeuronNetwork.cpp Edge.cpp)