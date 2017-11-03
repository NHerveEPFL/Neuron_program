#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "Neuron.hpp"
#include <vector>
#include <fstream>
#include <random>


class Network
{

private:

  //-----------------------attributes--------------------
  const unsigned int N_ = 12500; //-> number of neurons

  const unsigned int Ni_ = N_/5;   // -> number of inhibitory neurons
  const unsigned int Ne_ = 4*Ni_; //-> number of exitatory neurons

  const int Ci_ = Ni_/10; // -> number of inhibitory connections for 1 neuron
  const int Ce_ = Ne_/10; // -> number of exitatory connections for 1 neuron

  const int g_ = 5; // -> Ji/Je
  const double Je_ = 0.1; // -> weight send by exitatory neuron

/* table that contains all neurons, the first Ne_(10000) are exitatory, the
next Ni_(2500) are inhibitory
! Notice that to access a specific neuron n you need to choose n-1 !*/
  std::vector<Neuron*> Neurons_;

/* table that contains all connections between the neurons */
  //std::vector<std::vector<int>> neuronNetwork_;

  std::ofstream out_;

  std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
  std::poisson_distribution<unsigned int> d;  //-> table begins at 0 and ends at Ne-1 for exitatory


public:

/* implement Neurons_ with Ne_ neurons then Ni_ neurons
randomly create Ce_ and Ci_ connections between neurons */
  Network();

  Network(int Ne, int Ni);

  ~Network();


  void update(const double& I);
/* simulates interaction between two neurons (neuron 1 sends weight to neuron2)
*/
  void Interaction(Neuron n, const double& J) const;

  void Simulation(int steps);
};


#endif
