/*
 * PriorityQueueWorkingServers.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef PRIORITYQUEUEWORKINGSERVERS_H_
#define PRIORITYQUEUEWORKINGSERVERS_H_
#include "BoundedPriorityQueue.h"
#include "DataCenterRandom.h"
#include "PriorityQueueEventList.h"
#include "Accumulator.h"
#include "JobEvent.h"

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
typedef typename boost::numeric::ublas::matrix<double> Matrix;

class PriorityQueueWorkingServers : public BoundedPriorityQueue {
	std::ofstream logFile;
	std::string filename;
	double lastTime;
	double lastTotalPower;
	PriorityTypePtr sortOrder;
	DataCenterRandomPtr rand;
	PriorityQueueEventListPtr eventList;
	AccumulatorPtr latency;
	AccumulatorPtr totalEnergy;
	Matrix dppCalculator;
	Matrix voltages;
	Matrix serverCurrents;
	std::map<long, JobEventPtr > serverStack;
	double stringCurrent;
	long findWorstCaseIdleServer();
	bool invertMatrix(Matrix& input);
	void setupDPPCalculator();
	void updateStack(long i, JobEventPtr p, double time);
protected:
	virtual std::string name();
	virtual std::ostream& toStream(std::ostream& out);

public:
	PriorityQueueWorkingServers(
			long size,
			DataCenterRandomPtr rand,
			PriorityQueueEventListPtr eventList,
			AccumulatorPtr latency,
			AccumulatorPtr totalEnergy,
			PriorityTypePtr sortOrder,
			std::string filename);
	virtual ~PriorityQueueWorkingServers();

	virtual bool enqueue(JobEventPtr job, double time);
	virtual EventPtr dequeue();
	virtual void remove(JobEventPtr e, double time);
};

typedef typename boost::shared_ptr<PriorityQueueWorkingServers> PriorityQueueWorkingServersPtr;

#endif /* PRIORITYQUEUEWORKINGSERVERS_H_ */
