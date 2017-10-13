#ifndef NEURON_HPP
#define NEURON_HPP
#include <vector>



class Neuron
{


private:

//----------- attributes ----------------------


/** the membrane potential V_ depends of a Input_current and is always
 reset to a reset potential (V_res_) when it reaches the firing treshold
 (V_thr_) */

	double V_;
	const double V_thr_ = 20;
	const double V_res_ = 0;

/** usefull constant for fonction update :Tau_ = time constant
 *  R = membrane resistance*/
	const int Tau_ = 20; // -> in ms
	const int R_ = 20;




/** when the Membrane_potential_ is reset it has a little time during which
 it is insesitive to stimulation (called the refractory time (T_ref_) */
	const int T_ref_ = 2;   //->in ms


/** a spike is created each time the Membrane_potential_ reaches the
 Firing_treshold, Number_spikes_ counts the number of spikes that occure */
	int Number_spikes_;


/** each moment a spike occure will be labeled by this vector */
	std::vector <int> Times_spikes_;


/** keeps track of time inside the neuron */
	int Neuron_clock_;  // -> in ms


/* weight send by this neuron when a spike occures */
	double J_ = 0.4;
	size_t D_ = 5;

/* vector that memorizes delayed signals */
	std::vector<double> Delayed_weights_;







//--------------------- modules --------------------------


/* return a delayed signal from Delayed_weights_, returns 0 if there is none */
	double Delayed_signal();



public:

	Neuron();
	Neuron(double V);

	double getMembrane_potential() const;
	void setMembrane_potential(const double& V);

	int getNumber_spikes() const;
	void addSpike();

	std::vector <int> getTimes_spikes() const;
	void addTime_spike(const int& time);


/** update the membrane potential at all time */
	bool update(const double& Input_current, const int& step_time);

	double getWeight() const;
	size_t getDelay() const;

	void addDelayed_weight(double J, size_t Delay);

	double getDelayed_weight(size_t position) const;





};







#endif
