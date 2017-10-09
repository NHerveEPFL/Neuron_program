#include <iostream>
#include "Neuron.cpp"


int main()
{
	Neuron test;
	
	test.setMembrane_potential(-70.0);
	std::cout << "The membrane potential has a value of " <<
				 test.getMembrane_potential() << std::endl;
				 
	std::cout << "The number of spikes is alreaddy at "
				<< test.getNumber_spikes() << std::endl;
				 
	for(int i(0); i<=10; ++i)
	{
		test.addSpike();
		test.addTime_spike(i);
	}
	
	std::cout << "There is a total of " << test.getNumber_spikes()
				<< " spikes in this experiment" << std::endl;
				
				
	for(size_t i(0); i<test.getTimes_spikes().size(); ++i)
	{
		std::cout << "spike number " << i+1 << " ->  at "
					<< test.getTimes_spikes()[i] << " secondes"
					<< std::endl;
	}
	
	
	
	return 0;
}
			
			
