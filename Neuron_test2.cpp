#include <iostream>
#include "Neuron.hpp"
#include <fstream>




int main()
{
  Neuron N;
  Neuron H;

  size_t t_stop(500);
  double I(1.5);
  size_t step_time(1);
  bool Shappy(false);
  bool Ssad(false);

/*
  std::ofstream out;
  out.open("neuronTest.txt");
  */


  for ( size_t time=0; time<t_stop; ++time)
  {
    Shappy = N.update(I, step_time);
    Ssad = H.update(I, step_time);

    if (Shappy)
    {
      std::cout << " here we have -> " << H.getMembrane_potential() << std::endl;
      H.setMembrane_potential(H.getMembrane_potential()+N.getWeight());
      std::cout << " Now we have -> " << H.getMembrane_potential() << std::endl;
    }
  }




}
