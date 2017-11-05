#include <iostream>
#include "neuron.hpp"
#include "gtest/gtest.h"
#include <vector>


TEST(TwoNeurons_spikes,  )
{
  std::vector<Neuron*> miniNetwork;
  miniNetwork.push_back(new Neuron);
  miniNetwork.push_back(new Neuron);

  miniNetwork[0]->connect(1);

  for (int i(0); i < 1000; ++i )
  {
    if (miniNetwork[0]->update(1.01, 0))
    {
      miniNetwork[1]->
      addDelayed_weight(0.2, 15, miniNetwork[0]->getNeuron_clock());
    }
    miniNetwork[1]->update(0.0, 0);
  }
  EXPECT_EQ(1, miniNetwork[0]->getSpikes());
  EXPECT_DOUBLE_EQ(92.4, miniNetwork[1]->getTimes_spikes()[0]);

  EXPECT_EQ(0, miniNetwork[0]->getSpikes());

}


/*
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/
