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

class QueueJobBuffer {
	std::queue<JobEventPtr> queue;
	double rejected_time_delta;
	double last_rejected_time;
protected:
	virtual std::ostream& toStream(std::ostream& out){
		return(out << "QueueJobBuffer{size=" << this->queue.size() << "}");
	}
public:
	const long max_size;

	QueueJobBuffer(long size) : max_size(size) {
		this->last_rejected_time = -1;
		this->rejected_time_delta = -1;
	}
	virtual ~QueueJobBuffer() {
	}

	double getTimeBetweenRejections(){
		return rejected_time_delta;
	}

	bool is_full(){
		return this->queue.size() >= max_size;
	}

	bool is_empty(){
		return this->queue.size() == 0;
	}

	bool enqueue(JobEventPtr e){
		if(!this->is_full()){
			_logl(3,"Enqueueing " << *e);
			this->queue.push(e);
			return true;
		}
		else{
			_logl(3,"Rejecting enqueue request for " << *e);

			if(this->last_rejected_time != -1){
				this->rejected_time_delta = e->time - this->last_rejected_time;
			}
			this->last_rejected_time = e->time;
			return false;
		}
	}

	JobEventPtr dequeue(void){
		JobEventPtr p = this->queue.front();
		_logl(3,"Dequeueing " << *p);
		this->queue.pop();
		return p;
	}

	friend std::ostream& operator<< (std::ostream& out, QueueJobBuffer& e);
};

#endif /* QUEUEJOBBUFFER_H_ */
