#include "Neuron.hpp"
#include <vector>
#include <cmath>


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



bool Neuron::update(const double& Input_current, const int& step_time)
{
	if (V_ > V_thr_) 
	{
		V_ = V_res_;
		return true;
	}
	else 
	{
		V_ = exp(-step_time/Tau_)*V_ 
				+ Input_current*R_*(1-exp(-step_time/Tau);
		return false;
	}
}



