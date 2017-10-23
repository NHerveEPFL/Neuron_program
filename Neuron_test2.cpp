#include <iostream>
#include "Neuron.hpp"
#include <fstream>




int main()
{
  Neuron N;
  Neuron H(6.0);

  unsigned long t_stop(5000);
  double I(1.0);
  unsigned int step_time(1);
  bool Shappy(false);
  bool Ssad(false);



  std::ofstream outN;
  outN.open("neuron2Test.txt");


  std::ofstream outH;
  outH.open("neuron1Test.txt");



  for ( unsigned long time=0; time<t_stop; ++time)
  {
    Shappy = N.update(I, step_time);
    outN << N.getPot() << std::endl;
    /*std::cout << "at " << N.getNeuron_clock()*0.1
              << " membrane potential = "
              <<  N.getPot() << std::endl;*/


    Ssad = H.update(0.0, step_time);
    outH << H.getPot() << std::endl;

    if (Shappy)
    {
      H.addDelayed_weight(N.getWeight(),N.getDelay(),N.getNeuron_clock());
      /*std::cout << "at " << time*0.1 << " ms, a friendly neuron sends "
                << N.getWeight() << " to Jimmy" << std::endl;*/
    }
  }

  outH.close();
  outN.close();


}
