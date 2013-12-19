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

class PriorityQueueWorkingServers : public BoundedPriorityQueue {
	DataCenterRandomPtr rand;
	PriorityQueueEventListPtr eventList;
	AccumulatorPtr latency;
	AccumulatorPtr totalEnergy;
protected:
	virtual std::string name();

	virtual std::ostream& toStream(std::ostream& out);
public:
	PriorityQueueWorkingServers(
			long size,
			DataCenterRandomPtr rand,
			PriorityQueueEventListPtr eventList,
			AccumulatorPtr latency,
			AccumulatorPtr totalEnergy);

	virtual bool enqueue(JobEventPtr job, double time);

	virtual void remove(JobEventPtr e, double time);
};

typedef typename boost::shared_ptr<PriorityQueueWorkingServers> PriorityQueueWorkingServersPtr;

#endif /* PRIORITYQUEUEWORKINGSERVERS_H_ */
