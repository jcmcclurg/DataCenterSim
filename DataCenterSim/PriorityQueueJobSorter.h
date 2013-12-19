/*
 * PriorityQueueJobSorter.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef PRIORITYQUEUEJOBSORTER_H_
#define PRIORITYQUEUEJOBSORTER_H_

#include <boost/pointer_cast.hpp>
#include "BoundedPriorityQueue.h"
#include "PriorityQueueWorkingServers.h"
#include "DataCenterRandom.h"
#include "Event.h"
#include "JobEvent.h"
#include "Debug.h"

class PriorityQueueJobSorter : public BoundedPriorityQueue {
	PriorityQueueWorkingServersPtr workingServersQueue;
	DataCenterRandomPtr rand;
	PriorityQueueEventListPtr eventList;
protected:
	virtual std::string name();
	virtual std::ostream& toStream(std::ostream& out);
public:
	virtual bool enqueue(JobEventPtr job, double time);

	bool is_empty();

	virtual JobEventPtr dequeueJob();

	PriorityQueueJobSorter(
				long size,
				DataCenterRandomPtr rand,
				PriorityQueueWorkingServersPtr workingServersQueue,
				PriorityQueueEventListPtr eventList);
};

typedef typename boost::shared_ptr<PriorityQueueJobSorter> PriorityQueueJobSorterPtr;

#endif /* PRIORITYQUEUEJOBSORTER_H_ */
