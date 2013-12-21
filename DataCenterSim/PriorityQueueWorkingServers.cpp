/*
 * PriorityQueueWorkingServers.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */


#include "PriorityQueueWorkingServers.h"
#include <cstddef>
#include <cmath>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

// Reference: Numerical Recipies in C, 2nd ed., by Press, Teukolsky, Vetterling & Flannery.
// REMEMBER to update "lu.hpp" header includes from boost-CVS
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include "Debug.h"

typedef typename boost::numeric::ublas::zero_matrix<double> ZeroMatrix;
typedef typename boost::numeric::ublas::scalar_matrix<double> ScalarMatrix;
typedef typename boost::numeric::ublas::identity_matrix<double> IdentityMatrix;
typedef typename boost::numeric::ublas::permutation_matrix<std::size_t> PermutationMatrix;

typedef typename boost::numeric::ublas::zero_vector<double> ZeroVector;
typedef typename boost::numeric::ublas::scalar_vector<double> ScalarVector;
typedef typename boost::numeric::ublas::vector<double> Vector;

 /* Matrix inversion routine.
    Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
 bool PriorityQueueWorkingServers::invertMatrix(Matrix& input) {

	// create a permutation matrix for the LU-factorization
	PermutationMatrix pm(input.size1());

	// perform LU-factorization
	int res = boost::numeric::ublas::lu_factorize(input,pm);
		if( res != 0 ) return false;

	Matrix inverse(input);
	inverse.assign(IdentityMatrix(input.size1()));

	// backsubstitute to get the inverse
	boost::numeric::ublas::lu_substitute(input, pm, inverse);
	input.assign(inverse);

	return true;
}

std::string PriorityQueueWorkingServers::name(){
	return "Servers queue";
}

std::ostream& PriorityQueueWorkingServers::toStream(std::ostream& out){
	out << "PriorityQueueWorkingServers";
	BoundedPriorityQueue::toStream(out);
	out << "{Server currents = "<< this->serverCurrents << std::endl
		<< "Server voltages = " << this->voltages << std::endl
		<< "" << this->stringCurrent << std::endl
		<< "}";
	return(out);
}

/*
 The server stack is represented like so:
 Vbus
   | string current
   v
 serverStack[0] = JobEventPtr		(server working)
   |
   +-<---- differential current +
   |                               voltage for differential power calculation.
   v                            -
 serverStack[1] = nullptr			(server idle)
 ...
 */
// TODO: The search time is pretty horrendous.
long PriorityQueueWorkingServers::findWorstCaseIdleServer(){
	long worstI = 0;
	double worstCurrent = 0;
	for(long i = 0; i < this->max_size; i++){
		// If the server at this position is idle.
		if(!this->serverStack[i]){
			double desiredCurrent;
			double topCurrent;
			double bottomCurrent;
			if(i == this->max_size - 1){
				bottomCurrent = this->stringCurrent;
			}
			else{
				bottomCurrent = this->serverCurrents(i+1,0);
			}

			if( i == 0 ){
				topCurrent = this->stringCurrent;
			}
			else{
				topCurrent = this->serverCurrents(i-1,0);
			}

			desiredCurrent = (topCurrent + bottomCurrent)/2.0;
			if(desiredCurrent > worstCurrent){
				worstI = i;
				worstCurrent = desiredCurrent;
			}
		}
	}
	return worstI;
}

void PriorityQueueWorkingServers::updateStack(long i, JobEventPtr p, double time){
	double thisCurrent;
	if(p){
		_NOTEL(5,"Adding job to stack position " << i);
		thisCurrent = (p->powerConsumption)/this->voltages(i,0);
	}
	else{
		_NOTEL(5,"Removing job from stack position " << i);
		thisCurrent = 0;
	}

	// Update the server currents
	this->serverCurrents(i,0) = thisCurrent;

	// Recalculate the differentialCurrents
	Matrix differentialCurrents(this->max_size-1,1);
	differentialCurrents = boost::numeric::ublas::prod(this->dppCalculator,this->serverCurrents);

	this->stringCurrent = differentialCurrents(0,0)*0.5 + this->serverCurrents(0,0);

	// TODO: implement this as a dot product operation or matrix multiplication.
	double sum = 0;
	this->logFile << time << "," << this->serverCurrents(0,0);
	for(long x = 0; x < this->max_size - 1; x++){
		this->logFile << "," << this->serverCurrents(x+1,0);
		sum += std::abs(differentialCurrents(x,0))*this->voltages(x+1,0);
	}
	this->logFile << std::endl;

	// Update statistics
	if(lastTime != -1){
		this->totalEnergy->add(lastTotalPower*(time-lastTime),time);
	}
	lastTotalPower = sum;
	lastTime = time;

	double topCurrent;
	double bottomCurrent;
	if(i == this->max_size - 1){
		bottomCurrent = this->stringCurrent;
	}
	else{
		bottomCurrent = this->serverCurrents(i+1,0);
		if(this->serverStack[i+1]){
			this->serverStack[i+1]->topNeighborCurrent = thisCurrent;
		}
	}

	if( i == 0 ){
		topCurrent = this->stringCurrent;
	}
	else{
		topCurrent = this->serverCurrents(i-1,0);
		if(this->serverStack[i-1]){
			this->serverStack[i-1]->bottomNeighborCurrent = thisCurrent;
		}
	}
	if(p){
		p->topNeighborCurrent = topCurrent;
		p->bottomNeighborCurrent = bottomCurrent;
		p->stringIndex = i;
	}
	this->serverStack[i] = p;
}

// TODO: Maybe switch over to a faster matrix math library, or hard-code the special-case here.
void PriorityQueueWorkingServers::setupDPPCalculator(){
	long n = this->max_size;
	double duty = 0.5;
	double bus_voltage = 380.0;

	Matrix a(ZeroMatrix(n-1,n-1));
	Matrix b(ZeroMatrix(n-1,n-1));
	Matrix c(ZeroMatrix(n-1,n));
	Matrix d(ZeroMatrix(n-1,n-1));
	Matrix e(ZeroMatrix(n,n));
	Matrix f(ZeroMatrix(n,1));
	f(0,0) = bus_voltage;
	e(0,0) = 1;
	for(long i = 0; i < n-1; i++){
		if(i > 0){
			a(i,i-1) = -1;
			b(i,i-1) = 1;
		}
		b(i,i) = -1;
		c(i,i) = 1;
		c(i,i+1) = -1;
		d(i,i) = duty;
		e(0,i+1) = 1;
		e(i+1,i) = -duty;
		e(i+1,i+1) = 1-duty;
		if(i < n-2){
			a(i,i+1) = 1;
		}
	}
	a = boost::numeric::ublas::prod(a,d);
	a = a + b;
	this->invertMatrix(a);

	this->dppCalculator = boost::numeric::ublas::prod(a,c);
	this->invertMatrix(e);
	this->voltages = boost::numeric::ublas::prod(e,f);
}

EventPtr PriorityQueueWorkingServers::dequeue(){
	*(this->sortOrder) = JobEvent::DIFFERENTIAL_CURRENT;
	return BoundedPriorityQueue::dequeue();
}

PriorityQueueWorkingServers::PriorityQueueWorkingServers(
		long size,
		DataCenterRandomPtr rand,
		PriorityQueueEventListPtr eventList,
		AccumulatorPtr latency,
		AccumulatorPtr totalEnergy,
		PriorityTypePtr sortOrder,
		std::string filename,
		SortingDomain sorting_domain) :
				BoundedPriorityQueue(size),
				serverCurrents(size,1),
				dppCalculator(size-1,size) {
	this->sortOrder = sortOrder;
	this->rand = rand;
	this->eventList = eventList;
	this->latency = latency;
	this->totalEnergy = totalEnergy;
	this->stringCurrent = 0;
	this->lastTime = -1;
	this->lastTotalPower = 1;
	this->filename = filename;
	this->sorting_domain = sorting_domain;
	this->setupDPPCalculator();

	this->logFile.open(this->filename.c_str());

	for(long i = 0; i < this->max_size; i++){
		JobEventPtr j;
		this->serverStack[i] = j;
	}
}

PriorityQueueWorkingServers::~PriorityQueueWorkingServers(){
	this->logFile.close();
}

long PriorityQueueWorkingServers::findRandomIdleServer(){
	std::vector<long> idleServers;
	long i;
	for(i = 0; i < this->max_size; i++){
		// If the server at this position is idle.
		if(!this->serverStack[i]){
			idleServers.push_back(i);
		}
	}

	i = this->rand->sample_randomRouting(((long) (idleServers.size())) - 1);
	return idleServers[i];
}

// TODO: Fix implementation so that the priority queue saves us some search time. Right now, since we're doing the search separately, it's totally pointless to use a priority queue.
bool PriorityQueueWorkingServers::enqueue(JobEventPtr job, double time){
	*(this->sortOrder) = JobEvent::DIFFERENTIAL_CURRENT;
	double t = time + rand->sample_jobRoutingTime();
	_NOTEL(3,"Adding to working servers (busy until time " << t << ")");
	job->completionTime = rand->sample_completionTime();
	job->powerConsumption = rand->sample_power();
	if(BoundedPriorityQueue::enqueue(job)){
		if(this->sorting_domain == PriorityQueueWorkingServers::POWER_AWARE){
			updateStack(findWorstCaseIdleServer(),job, time);
		}
		else{ // if(this->sorting_domain == PriorityQueueWorkingServers::RANDOM){
			updateStack(findRandomIdleServer(),job, time);
		}
		EventPtr ready(new Event(t, Event::WORKING_SERVERS_QUEUE_READY));
		eventList->enqueue(ready);

		job->time = time + job->completionTime;
		job->type = Event::JOB_FINISHED;
		eventList->enqueue(job);

		_NOTEL(5, (*this) );
		return true;
	}
	_NOTEL(3,"Working servers queue rejecting enqueue request for " << *job);
	return false;
}

void PriorityQueueWorkingServers::remove(JobEventPtr e, double time){
	*(this->sortOrder) = JobEvent::DIFFERENTIAL_CURRENT;
	typedef typename SortedEventQueue::handle_type handle_t;

	for (SortedEventQueue::iterator it = this->queue.begin(); it != this->queue.end(); ++it){
		EventPtr ptr = *it;
		JobEventPtr job = boost::static_pointer_cast<JobEvent>(ptr);
		if(*job == *e){
			_NOTEL(3,"Removing element " << *job);
			JobEventPtr j;
			this->updateStack(job->stringIndex, j, time);
			this->latency->add(time - job->originalTime, time);

			handle_t h = SortedEventQueue::s_handle_from_iterator(it);
			this->queue.erase(h);

			_NOTEL(5, (*this) );
			return;
		}
	}
	_NOTEL(3,"Could not find element " << *e);
}
