#include <iostream>
#include "neuron.hpp"
#include "Network.hpp"
#include "gtest/gtest.h"

TEST(OneNeuron, spikes_1000_steps)
{
  Neuron n;
  for (int i(0); i < 1000; ++i )
  {
    n.update(1.01,0);
  }
  EXPECT_EQ(1, n.getSpikes());
  EXPECT_DOUBLE_EQ(92.4, n.getTimes_spikes()[0]);
}

TEST(OneNeuron, spikes_4000_steps)
{
  Neuron n;
  for (int i(0); i < 4000; ++i )
  {
    n.update(1.01, 0);
  }
  EXPECT_EQ(4, n.getSpikes());
  EXPECT_DOUBLE_EQ(92.4, n.getTimes_spikes()[0]);
  EXPECT_DOUBLE_EQ(186.8, n.getTimes_spikes()[1]);
  EXPECT_DOUBLE_EQ(281.2, n.getTimes_spikes()[2]);
  EXPECT_DOUBLE_EQ(375.6, n.getTimes_spikes()[3]);
}

TEST(OneNeuron, MembranePotentialSmallerThan20_10000steps)
{
  Neuron n;
  bool smaller20(true);
  for (int i(0); i < 10000; ++i )
  {
    n.update(1.01, 0);
    if (n.getPot() > 20)
    { smaller20 = false; }
  }
  EXPECT_TRUE(smaller20);
}

TEST(OneNeuron, Input_of_1)
{
  Neuron n;
  for (int i(0); i < 10000; ++i )
  {
    n.update(1.0,0);
  }
  EXPECT_EQ(0, n.getSpikes());
}

TEST(OneNeuron, Input_of_0)
{
  Neuron n;
  bool zero(true);
  for (int i(0); i < 10000; ++i )
  {
    n.update(0.0,0);
    if(std::abs(n.getPot()-0.0) > 1e-15)
    {
      zero = false;
    }
  }
  EXPECT_TRUE(zero);
}



TEST(TwoNeurons, exitatory)
{
  std::vector<Neuron*> miniNetwork(0);
  miniNetwork.push_back(new Neuron);
  miniNetwork.push_back(new Neuron);

  miniNetwork[0]->connect(1);

  for (int i(0); i < 1000; ++i )
  {
    if (miniNetwork[0]->update(1.01, 0))
    {
      miniNetwork[1]->
      addDelayed_weight(0.1, 15, miniNetwork[0]->getNeuron_clock());
    }
    miniNetwork[1]->update(0.0, 0);
    if (i == 938)
    { EXPECT_DOUBLE_EQ(0.1, miniNetwork[1]->getPot()); }
  }

  EXPECT_EQ(1, miniNetwork[0]->getSpikes());
  EXPECT_DOUBLE_EQ(92.4, miniNetwork[0]->getTimes_spikes()[0]);

  EXPECT_EQ(0, miniNetwork[1]->getSpikes());

  for ( auto& neuron : miniNetwork )
  {
    neuron = nullptr;
    delete neuron;
  }

}


TEST(TwoNeurons, inhibitory)
{
  std::vector<Neuron*> miniNetwork(0);
  miniNetwork.push_back(new Neuron);
  miniNetwork.push_back(new Neuron);

  miniNetwork[0]->connect(1);

  for (int i(0); i < 1000; ++i )
  {
    if (miniNetwork[0]->update(1.01, 0))
    {
      miniNetwork[1]->
      addDelayed_weight(-0.5, 15, miniNetwork[0]->getNeuron_clock());
    }
    miniNetwork[1]->update(0.0, 0);
    if (i == 938)
    { EXPECT_DOUBLE_EQ(-0.5, miniNetwork[1]->getPot()); }
  }

  EXPECT_EQ(1, miniNetwork[0]->getSpikes());
  EXPECT_DOUBLE_EQ(92.4, miniNetwork[0]->getTimes_spikes()[0]);

  EXPECT_EQ(0, miniNetwork[1]->getSpikes());

  for ( auto& neuron : miniNetwork )
  {
    neuron = nullptr;
    delete neuron;
  }
}

TEST(Network, constructor)
{
  Network myBrain;
  int NetworkSize(myBrain.getNeurons().size());
  //need a int to avoid warning in EXPECT_EQ

  EXPECT_EQ (12500, NetworkSize);
}



/*
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/
