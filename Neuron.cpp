#include "Neuron.hpp"
#include <vector>
#include <cmath>
#include <iostream>


Neuron::Neuron()
:V_(0.0), Number_spikes_(0)
{}


double Neuron::getMembrane_potential() const
{ return V_; }

void Neuron::setMembrane_potential(const double& V)
{ V_ = V; }


int Neuron::getNumber_spikes() const
{ return Number_spikes_; }

void Neuron::addSpike()
{ ++ Number_spikes_; }


std::vector<int> Neuron::getTimes_spikes() const
{ return Times_spikes_; }

void Neuron::addTime_spike(const int& time)
{ Times_spikes_.push_back(time); }


double Neuron::getWeight() const
{ return J_; }


bool Neuron::update(const double& Input_current, const int& step_time)
{

	if (Times_spikes_.empty())
	{
		if (V_ < V_thr_)
		{
			V_ = exp(-step_time*0.1/Tau_)*V_
					+ Input_current*R_*(1-exp(-step_time*0.1/Tau_));


			Neuron_clock_+= step_time;
			//std::cout << "step 1" << std::endl;

			return false;
		}

		else
		{
			this->addSpike();
			this->addTime_spike(Neuron_clock_);

			V_ = V_res_;

			Neuron_clock_+= step_time;
			//std::cout << "step 2" << std::endl;
			std::cout << "spike at time " << Neuron_clock_ << std::endl;

			return true;
		}
	}


	else if (abs(Times_spikes_.back()-Neuron_clock_) < T_ref_)
	{
		V_ = V_res_;

		Neuron_clock_+= step_time;
		//std::cout << "step 3" << Neuron_clock_ << std::endl;
		return false;
	}


	else
	{
		if (V_ > V_thr_)
		{
			this->addSpike();
			this->addTime_spike(Neuron_clock_);

			V_ = V_res_;

			Neuron_clock_+= step_time;
			std::cout << "spike at time " << Neuron_clock_ << std::endl;

			return true;
		}

		else
		{
			V_ = exp(-step_time*0.1/Tau_)*V_
					+ Input_current*R_*(1-exp(-step_time*0.1/Tau_));

			Neuron_clock_+= step_time;
			//std::cout << "step 5 " << std::endl;
			return false;
		}
	}

	return false;
}
