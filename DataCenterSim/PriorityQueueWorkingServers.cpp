/*
 * PriorityQueueWorkingServers.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */


#include "PriorityQueueWorkingServers.h"

std::string PriorityQueueWorkingServers::name(){
	return "Servers queue";
}

std::ostream& PriorityQueueWorkingServers::toStream(std::ostream& out){
	out << "PriorityQueueWorkingServers";
	BoundedPriorityQueue::toStream(out);
	return(out);
}

PriorityQueueWorkingServers::PriorityQueueWorkingServers(
		long size,
		DataCenterRandomPtr rand,
		PriorityQueueEventListPtr eventList,
		AccumulatorPtr latency,
		AccumulatorPtr totalEnergy) : BoundedPriorityQueue(size){
	this->rand = rand;
	this->eventList = eventList;
	this->latency = latency;
	this->totalEnergy = totalEnergy;
}

bool PriorityQueueWorkingServers::enqueue(JobEventPtr job, double time){
	double t = time + rand->sample_jobRoutingTimeDistribution();
	_logl(3,"Adding to working servers (busy until time " << t << ")");
	job->completionTime = rand->sample_completionTimeDistribution();
	job->priorityIndicator = JobEvent::DIFFERENTIAL_CURRENT;
	if(BoundedPriorityQueue::enqueue(job)){
		EventPtr ready(new Event(t, Event::WORKING_SERVERS_QUEUE_READY));
		eventList->enqueue(ready);

		job->time = time + job->completionTime;
		job->priorityIndicator = JobEvent::TIME;
		job->type = Event::JOB_FINISHED;
		eventList->enqueue(job);
		return true;
	}
	_logl(3,"Working servers queue rejecting enqueue request for " << *job);
	return false;
}

void PriorityQueueWorkingServers::remove(JobEventPtr e, double time){
	typedef typename SortedEventQueue::handle_type handle_t;

	for (SortedEventQueue::iterator it = this->queue.begin(); it != this->queue.end(); ++it){
		EventPtr ptr = *it;
		JobEventPtr job = boost::static_pointer_cast<JobEvent>(ptr);
		if(*job == *e){
			_logl(3,"Removing element " << *job);
			this->latency->add(time - job->originalTime);

			handle_t h = SortedEventQueue::s_handle_from_iterator(it);
			this->queue.erase(h);
			return;
		}
	}
	_logl(3,"Could not find element " << *e);
}
