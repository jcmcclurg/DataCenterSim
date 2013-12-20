/*
 * PriorityQueueJobSorter.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "PriorityQueueJobSorter.h"

std::string PriorityQueueJobSorter::name(){
	return "Sorted queue";
}
std::ostream& PriorityQueueJobSorter::toStream(std::ostream& out){
	out << "PriorityQueueJobSorter";
	BoundedPriorityQueue::toStream(out);
	return(out);
}
bool PriorityQueueJobSorter::enqueue(JobEventPtr job, double time){
	if(!is_empty() || workingServersQueue->is_busy() || workingServersQueue->is_full()){
		*(this->sortOrder) = JobEvent::POWER_ESTIMATE;

		double t = time + rand->sample_jobSortingTimeDistribution();
		_logl(3,"Adding to sorting queue (busy until time " << t << ")");
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

bool PriorityQueueJobSorter::is_empty(){
	return this->queue.size() == 0;
}

EventPtr PriorityQueueJobSorter::dequeue(){
	*(this->sortOrder) = JobEvent::POWER_ESTIMATE;
	return BoundedPriorityQueue::dequeue();
}

JobEventPtr PriorityQueueJobSorter::dequeueJob(){
	*(this->sortOrder) = JobEvent::POWER_ESTIMATE;
	return boost::static_pointer_cast<JobEvent>(BoundedPriorityQueue::dequeue());
}

PriorityQueueJobSorter::PriorityQueueJobSorter(
			long size,
			DataCenterRandomPtr rand,
			PriorityQueueWorkingServersPtr workingServersQueue,
			PriorityQueueEventListPtr eventList,
			PriorityTypePtr sortOrder) : BoundedPriorityQueue(size){
	this->rand = rand;
	this->workingServersQueue = workingServersQueue;
	this->eventList = eventList;
	this->sortOrder = sortOrder;
}
