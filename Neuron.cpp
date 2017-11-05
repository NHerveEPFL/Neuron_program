#include "Neuron.hpp"
#include <vector>
#include <iostream>
#include <random>



/* maximum delay possible = 100 */
Neuron::Neuron()
:V_(0.0), Number_spikes_(0), Ref_(0), Delayed_weights_(D_+1, 0.0)
{
	Neuron_clock_ = 0;
}

Neuron::Neuron(double V)
:V_(V), Number_spikes_(0), Delayed_weights_(10,0)
{}


double Neuron::getPot() const
{ return V_; }

void Neuron::setPot(const double& V)
{ V_ = V; }


int Neuron::getSpikes() const
{ return Number_spikes_; }

void Neuron::addSpike()
{ ++ Number_spikes_; }


std::vector<double> Neuron::getTimes_spikes() const
{ return Times_spikes_; }

void Neuron::addTime_spike(const double& time)
{ Times_spikes_.push_back(time); }

size_t Neuron::getDelay() const
{ return D_; }

double Neuron::getNeuron_clock() const
{ return Neuron_clock_*h_; }

double Neuron::getDelayed_weight(size_t position) const
{ return Delayed_weights_[position%Delayed_weights_.size()]; }


void Neuron::addDelayed_weight
(const double& J, const unsigned long& D, const unsigned long& time)
{
	size_t position = (time+D) % Delayed_weights_.size();
	Delayed_weights_[position] += J;
}


bool Neuron::update(const double& I, int poisson)
{
	bool spike(false);

	if (Ref_ > 0)
	{
/* if the neuron is refractory it is insesitive to signals but that doesn't
mean the signal is stored, to get rid of the signal I implement it to V_ before
reinitializing V_ (thus the signal is lost)*/
		V_ += Delayed_signal();
		V_ = V_res_;
		-- Ref_;
	}

	else
	{

		V_ = C1_*V_ + I*C2_ + Delayed_signal() + poisson*J_;
	}

	if (V_ > V_thr_)
	{
		addSpike();
		addTime_spike(getNeuron_clock()+h_);
		V_ = 0;
		Ref_ = T_ref_;
		spike = true;
	}

	++ Neuron_clock_;

	return spike;
}


double Neuron::Delayed_signal()
{

	size_t bufferTime ((Neuron_clock_+1) % Delayed_weights_.size());
	double weight (Delayed_weights_[bufferTime]);
	Delayed_weights_[bufferTime] = 0.0;

	return weight;
}


void Neuron::connect(const int& target)
{	Targets_.push_back(target); }

std::vector <int> Neuron::getTargets() const
{ return Targets_; }
