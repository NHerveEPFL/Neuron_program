#include "Neuron.hpp"
#include <vector>
#include <cmath>
#include <iostream>


/* maximum delay possible = 100 */
Neuron::Neuron()
:V_(0.0), Number_spikes_(0), Delayed_weights_(D_+1, 0.0)
{}

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


std::vector<int> Neuron::getTimes_spikes() const
{ return Times_spikes_; }

void Neuron::addTime_spike(const unsigned long& time)
{ Times_spikes_.push_back(time); }


double Neuron::getWeight() const
{ return J_; }

size_t Neuron::getDelay() const
{ return D_; }

int Neuron::getNeuron_clock() const
{ return Neuron_clock_; }

double Neuron::getDelayed_weight(size_t position) const
{ return Delayed_weights_[position%Delayed_weights_.size()]; }


void Neuron::addDelayed_weight
(const double& J, const unsigned long& D, const unsigned long& time)
{
	size_t position = (time+D) % Delayed_weights_.size();

	Delayed_weights_[position] += J;
}


bool Neuron::update(const double& I, const unsigned int& step_time)
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

	/*if (Times_spikes_.empty())
	{
		if (V_ < V_thr_)
		{
			V_ = exp(step_time*(-h_)/Tau_)*V_
					+ I*R_*(1-exp(step_time*(-h_)/Tau_))
					+ Delayed_signal();


			Neuron_clock_+= step_time;

			return false;
		}*/
		else
		{
			V_ = exp(step_time*(-h_)/Tau_)*V_
					+ I*R_*(1-exp(step_time*(-h_)/Tau_))
					+ Delayed_signal();
		}

		if (V_ > V_thr_)
		{
			addSpike();
			addTime_spike(Neuron_clock_);
			Ref_ = T_ref_;
			spike = true;
		}

	/*	else
		{
			addSpike();
			addTime_spike(Neuron_clock_);





			Neuron_clock_+= step_time;

			return true;
		}
	}


	else if (abs(Times_spikes_.back()-Neuron_clock_) < T_ref_)
	{


		V_ += Delayed_signal();
		V_ = V_res_;

		Neuron_clock_+= step_time;

		return false;
	}
	*/


	/*else
	{
		if (V_ > V_thr_)
		{
			addSpike();
			addTime_spike(Neuron_clock_);

			V_ += Delayed_signal();
			V_ = V_res_;

			Neuron_clock_+= step_time;

			return true;
		}

		else
		{
			V_ = exp(step_time*(-h_)/Tau_)*V_
					+ I*R_*(1-exp(step_time*(-h_)/Tau_))
					+ Delayed_signal();

			Neuron_clock_+= step_time;

			return false;
		}
	}

	return false;*/
	++ Neuron_clock_;

	return spike;
}


double Neuron::Delayed_signal()
{

	size_t bufferTime ((Neuron_clock_+1) % Delayed_weights_.size());
	double weight (Delayed_weights_[bufferTime]);
	Delayed_weights_[bufferTime] = 0.0;

/*
	if (weight > 0.01)
	{
		std::cout << "at " << Neuron_clock_*0.1 << " ms, Jimmy receives " << weight
							<< " from a friendly Neuron" << std::endl;
	}
	*/

	return weight;
}
