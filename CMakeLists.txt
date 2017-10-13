cmake_minimum_required (VERSION 2.6)
project (Neuron)

set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")
add_executable (Neuron Neuron_test2.cpp Neuron.cpp)
