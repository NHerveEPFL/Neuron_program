#include <iostream>
#include "Neuron.hpp"
#include <fstream>



int main()
{
/* the test creats a Neuron, a Input current I and a time stop that indicates
when to end the experiment aswell as a step time */
	Neuron jimmy;
	size_t t_stop(5000);
	double I(1.5);
	size_t step_time(1);
	bool S(false);

	std::ofstream out;
	out.open("neuronTest.txt");

	for ( size_t time=0; time<t_stop; ++time)
	{
/** does a update and return true if a spike occured */
		S = jimmy.update(I, step_time);
		out << jimmy.getMembrane_potential() << std::endl;

	}

	std::cout << std::endl << "conclusion:  Number of spikes = "
			<< jimmy.getNumber_spikes() << std::endl;

	out.close();

	return 0;
}
