#include <iostream>
#include "Network.hpp"

int main()
{

  Network myBrain; //-> default network creation

  for(int i(0); i < 2000; ++i)
  {
    myBrain.update(0.0);
  }

  return 0;
}


/* file << spike_time << '\t' << neuron_id(=#neurons) << '\n';
target[gid][tid] (=neuron number and target neuron)
you need a list of target for each neuron
create function connect to create list which you can implement in Network
# <cassert>
Doxygen :  //!< comment
don't forget eta (=2.0)

*/
