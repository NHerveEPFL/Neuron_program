#include <iostream>
#include "Neuron.hpp"
#include <fstream>




int main()
{
  Neuron N;
  Neuron H(6.0);

  size_t t_stop(5000);
  double I(1.5);
  size_t step_time(1);
  bool Shappy(false);
  bool Ssad(false);



  std::ofstream outN;
  outN.open("neuron2Test.txt");


  std::ofstream outH;
  outH.open("neuron1Test.txt");



  for ( size_t time=0; time<t_stop; ++time)
  {
    Shappy = N.update(I, step_time);
    outN << N.getMembrane_potential() << std::endl;

    Ssad = H.update(I, step_time);
    outH << H.getMembrane_potential() << std::endl;

    if (Shappy)
    {
      H.addDelayed_weight(N.getWeight(),N.getDelay());
      std::cout << "at " << time << " ms, a friendly neuron sends "
                << N.getWeight() << " to Jimmy" << std::endl;
    }
  }

  outH.close();
  outN.close();


}
