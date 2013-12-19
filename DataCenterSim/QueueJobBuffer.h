/*
 * QueueJobBuffer.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef QUEUEJOBBUFFER_H_
#define QUEUEJOBBUFFER_H_

#include "JobEvent.h"

class QueueJobBuffer {
	std::queue<JobEventPtr> queue;

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
			this->queue.push(e);
		}
	}

	JobEventPtr dequeue(void){
		JobEventPtr p = this->queue.front();
		this->queue.pop();
		return p;
	}
};

#endif /* QUEUEJOBBUFFER_H_ */
