/*
 * QueueJobBuffer.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "QueueJobBuffer.h"

std::ostream& operator<< (std::ostream& out, QueueJobBuffer& e){
	return e.toStream(out);
}

std::ostream& QueueJobBuffer::toStream(std::ostream& out){
	return(out << "QueueJobBuffer{size=" << this->queue.size() << "}");
}

QueueJobBuffer::QueueJobBuffer(
		long size,
		AccumulatorPtr time_between_rejected_jobs,
		PriorityQueueJobSorterPtr sortedJobQueue) : max_size(size) {
	this->last_rejected_time = -1;
	this->time_between_rejected_jobs = time_between_rejected_jobs;
	this->sortedJobQueue = sortedJobQueue;
}

bool QueueJobBuffer::is_full(){
	return this->queue.size() >= max_size;
}

bool QueueJobBuffer::is_empty(){
	return this->queue.size() == 0;
}

bool QueueJobBuffer::enqueue(JobEventPtr e){
	if(!is_empty() || sortedJobQueue->is_busy() || sortedJobQueue->is_full()){
		if(!this->is_full()){
			_logl(4,"Job buffer enqueueing " << *e);
			this->queue.push(e);
			return true;
		}
		else{
			_logl(4,"Job buffer full. Rejecting enqueue request for " << *e);

			if(this->last_rejected_time != -1){
				time_between_rejected_jobs->add(e->time - this->last_rejected_time, e->time);
			}
			this->last_rejected_time = e->time;
		}
	}
	_logl(4,"Job buffer forwarding enqueue request for " << *e);
	return false;
}

JobEventPtr QueueJobBuffer::dequeue(void){
	JobEventPtr p = this->queue.front();
	_logl(4,"Job buffer dequeueing " << *p);
	this->queue.pop();
	return p;
}
