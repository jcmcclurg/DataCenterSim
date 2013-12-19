/*
 * QueueJobBuffer.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef QUEUEJOBBUFFER_H_
#define QUEUEJOBBUFFER_H_

#include <iostream>
#include <sstream>
#include <queue>
#include "JobEvent.h"
#include "Debug.h"
#include "Accumulator.h"
#include "PriorityQueueJobSorter.h"

class QueueJobBuffer {
	std::queue<JobEventPtr> queue;
	double last_rejected_time;
	AccumulatorPtr time_between_rejected_jobs;
	PriorityQueueJobSorterPtr sortedJobQueue;
protected:
	virtual std::ostream& toStream(std::ostream& out){
		return(out << "QueueJobBuffer{size=" << this->queue.size() << "}");
	}
public:
	const long max_size;

	QueueJobBuffer(
			long size,
			AccumulatorPtr time_between_rejected_jobs,
			PriorityQueueJobSorterPtr sortedJobQueue) : max_size(size) {
		this->last_rejected_time = -1;
		this->time_between_rejected_jobs = time_between_rejected_jobs;
		this->sortedJobQueue = sortedJobQueue;
	}
	virtual ~QueueJobBuffer() {
	}

	bool is_full(){
		return this->queue.size() >= max_size;
	}

	bool is_empty(){
		return this->queue.size() == 0;
	}

	bool enqueue(JobEventPtr e){
		if(!is_empty() || sortedJobQueue->is_busy() || sortedJobQueue->is_full()){
			if(!this->is_full()){
				_logl(4,"Job buffer enqueueing " << *e);
				this->queue.push(e);
				return true;
			}
			else{
				_logl(4,"Job buffer full. Rejecting enqueue request for " << *e);

				if(this->last_rejected_time != -1){
					time_between_rejected_jobs->add(e->time - this->last_rejected_time);
				}
				this->last_rejected_time = e->time;
			}
		}
		_logl(4,"Job buffer forwarding enqueue request for " << *e);
		return false;
	}

	JobEventPtr dequeue(void){
		JobEventPtr p = this->queue.front();
		_logl(4,"Job buffer dequeueing " << *p);
		this->queue.pop();
		return p;
	}

	friend std::ostream& operator<< (std::ostream& out, QueueJobBuffer& e);
};

typedef typename boost::shared_ptr<QueueJobBuffer> QueueJobBufferPtr;

#endif /* QUEUEJOBBUFFER_H_ */
