#ifndef NEURON_HPP
#define NEURON_HPP
#include <vector>
#include <cmath>
#include <cstddef>  //-> is needed on SV workspace to use size_t


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

/* gives the step time in ms (real time) */
	const double h_ = 0.1;


/* weight send by this neuron when a spike occures */
	const double J_ = 0.1;
/* delay at which the signal will arrive */
	const unsigned long D_ = 15;



/** when the Membrane_potential_ is reset it has a little time during which
 it is insesitive to stimulation (called the refractory time (T_ref_) */
	const int T_ref_ = 20;   //->in [0.1 * ms] this is thus 2 ms



const double C1_ = exp(-h_/Tau_);
const double C2_ = R_*(1-exp(-h_/Tau_));


/* a spike is created each time the Membrane_potential_ reaches the
 Firing_treshold, Number_spikes_ counts the number of spikes that occure */
	int Number_spikes_;

/*counter that checks the refractory state (Ref_ > 0) = Ref state*/
	int Ref_;


/* each moment a spike occure will be labeled by this vector */
	std::vector <double> Times_spikes_;


/* keeps track of time inside the neuron */
	int Neuron_clock_;  // -> in step value (real time = clock*h_)


/* vector that memorizes delayed signals */
	std::vector<double> Delayed_weights_;


/* list of target neurons */
	std::vector<int> Targets_;



//--------------------- modules --------------------------





public:

	Neuron();
	Neuron(double V);

/*returns/set membrane potential */
	double getPot() const;
	void setPot(const double& V);

/*returns number of spikes */
	int getSpikes() const;
	void addSpike();

/* returns real time value of Neuron_clock_ (in ms) */
	double getNeuron_clock() const;

	std::vector <double> getTimes_spikes() const;
	void addTime_spike(const double& time);


/** update the membrane potential at all time
@param I : input current */
	bool update(const double& I, int poisson);

	double getWeight() const;
	size_t getDelay() const;

/* @param J : weight to add (weight = part of Input current)
	@param D : delay at which the weight will come */
	void addDelayed_weight(const double& J, const unsigned long& D, const unsigned long& time);

	double getDelayed_weight(size_t position) const;

/*Normaly I don't need to use Delayed_weights_ in the main so I can put this
module inside the private part - see test2*/
/* return a delayed signal from Delayed_weights_, returns 0 if there is none
and clears the value once it is used */
	double Delayed_signal();

	void connect(const int& target);

 	std::vector <int> getTargets() const;


};







#endif
