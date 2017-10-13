#include "Neuron.hpp"
#include <vector>
#include <cmath>
#include <iostream>

/* maximum delay possible = 100 */
Neuron::Neuron()
:V_(0.0), Number_spikes_(0), Delayed_weights_(10,0)
{}

Neuron::Neuron(double V)
:V_(V), Number_spikes_(0), Delayed_weights_(10,0)
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

size_t Neuron::getDelay() const
{ return D_; }


bool Neuron::update(const double& Input_current, const int& step_time)
{

	if (Times_spikes_.empty())
	{
		if (V_ < V_thr_)
		{
			V_ = exp(-step_time*0.1/Tau_)*V_
					+ Input_current*R_*(1-exp(-step_time*0.1/Tau_))
					+ Delayed_signal();


			Neuron_clock_+= step_time;

			return false;
		}

		else
		{
			this->addSpike();
			this->addTime_spike(Neuron_clock_);

/* if the neuron is refractory it is insesitive to signals but that doesn't
mean the signal is stored, to get rid of the signal I implement it to V_ before
reinitializing V_ (thus the signal is lost)*/

			V_ += Delayed_signal();
			V_ = V_res_;

			Neuron_clock_+= step_time;

			return true;
		}
	}


	else if (abs(Times_spikes_.back()-Neuron_clock_) < T_ref_)
	{

/* if the neuron is refractory it is insesitive to signals but that doesn't
mean the signal is stored, to get rid of the signal I implement it to V_ before
reinitializing V_ (thus the signal is lost)*/

		V_ += Delayed_signal();
		V_ = V_res_;

		Neuron_clock_+= step_time;

		return false;
	}


	else
	{
		if (V_ > V_thr_)
		{
			this->addSpike();
			this->addTime_spike(Neuron_clock_);

			V_ += Delayed_signal();
			V_ = V_res_;

			Neuron_clock_+= step_time;

			return true;
		}

		else
		{
			V_ = exp(-step_time*0.1/Tau_)*V_
					+ Input_current*R_*(1-exp(-step_time*0.1/Tau_))
					+Delayed_signal();

			Neuron_clock_+= step_time;

			return false;
		}
	}

	return false;
}


void Neuron::addDelayed_weight(double J, size_t Delay)
{
	size_t position = (Neuron_clock_+Delay)%Delayed_weights_.size();

	Delayed_weights_[position] += J;

}


double Neuron::getDelayed_weight(size_t position) const
{ return Delayed_weights_[position]; }


double Neuron::Delayed_signal()
{

	size_t bufferTime ((Neuron_clock_+1) % Delayed_weights_.size());
	double weight (Delayed_weights_[bufferTime]);
	Delayed_weights_[bufferTime] = 0;


	if (weight > 0.01)
	{
		std::cout << "at " << Neuron_clock_ << " ms, Jimmy recieves " << weight
							<< " from a friendly Neuron" << std::endl;
	}

	return weight;
}
