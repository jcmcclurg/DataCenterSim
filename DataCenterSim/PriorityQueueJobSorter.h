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
	virtual std::string name(){
		return "Sorted queue";
	}
	virtual std::ostream& toStream(std::ostream& out){
		out << "PriorityQueueJobSorter";
		BoundedPriorityQueue::toStream(out);
		return(out);
	}
public:
	virtual bool enqueue(JobEventPtr job, double time){
		if(!is_empty() || workingServersQueue->is_busy() || workingServersQueue->is_full()){
			double t = time + rand->sample_jobSortingTimeDistribution();
			_logl(3,"Adding to sorting queue (busy until time " << t << ")");
			job->priorityIndicator = JobEvent::POWER_ESTIMATE;
			job->powerConsumption = rand->sample_powerDistribution();
			job->powerConsumptionEstimate = rand->sample_powerEstimate(job->powerConsumption);

			if(BoundedPriorityQueue::enqueue(job)){
				EventPtr ready(new Event(t, Event::SORTED_QUEUE_READY));
				eventList->enqueue(ready);
				return true;
			}
		}
		_logl(3,"Sorted queue forwarding enqueue request for " << *job);
		return false;
	}

	bool is_empty(){
		return this->queue.size() == 0;
	}

	virtual JobEventPtr dequeueJob(){
		return boost::static_pointer_cast<JobEvent>(BoundedPriorityQueue::dequeue());
	}

	PriorityQueueJobSorter(
				long size,
				DataCenterRandomPtr rand,
				PriorityQueueWorkingServersPtr workingServersQueue,
				PriorityQueueEventListPtr eventList) : BoundedPriorityQueue(size){
		this->rand = rand;
		this->workingServersQueue = workingServersQueue;
		this->eventList = eventList;
	}
};

typedef typename boost::shared_ptr<PriorityQueueJobSorter> PriorityQueueJobSorterPtr;

#endif /* PRIORITYQUEUEJOBSORTER_H_ */
