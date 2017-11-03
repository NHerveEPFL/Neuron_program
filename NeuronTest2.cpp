#include <iostream>
#include "Neuron.hpp"
#include <fstream>
#include "Network.hpp"




int main()
{
  Neuron N;
  Neuron H(6.0);

  unsigned long t_stop(4000);
  double I(1.01);

  bool Shappy(false);
  bool Ssad(false);


  std::ofstream outN;
  outN.open("neuron1Test.txt");


  std::ofstream outH;
  outH.open("neuron2Test.txt");



  for ( unsigned long time=0; time<t_stop; ++time)
  {
    Shappy = N.update(I);
    outN << "at " << N.getNeuron_clock() << " ms -> " << N.getPot() << std::endl;



    Ssad = H.update(0.0);
    outH << "at " << H.getNeuron_clock() << " ms -> " << H.getPot() << std::endl;


    if (Shappy)
    {
      H.addDelayed_weight(N.getWeight(),N.getDelay(),N.getNeuron_clock());
    }
  }


/*
  for (size_t i(0); i < N.getTimes_spikes().size(); ++i)
  {
      std::cout << N.getTimes_spikes()[i] << std::endl;
  }
*/

  outH.close();
  outN.close();


}
