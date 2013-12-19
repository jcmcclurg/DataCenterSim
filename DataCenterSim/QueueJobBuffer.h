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
protected:
	virtual std::ostream& toStream(std::ostream& out){
		return(out << "QueueJobBuffer{size=" << this->queue.size() << "}");
	}
public:
	const long max_size;

	QueueJobBuffer(long size) : max_size(size) {
	}
	virtual ~QueueJobBuffer() {
	}

	bool is_full(){
		return this->queue.size() >= max_size;
	}

	void enqueue(JobEventPtr e){
		if(!this->is_full()){
			_logl(3,"Enqueueing " << *e);
			this->queue.push(e);
		}
		else{
			_logl(3,"Silently ignoring enqueue request for " << *e);
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
