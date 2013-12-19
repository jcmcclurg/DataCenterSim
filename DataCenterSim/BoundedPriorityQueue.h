/*
 * BoundedPriorityQueue.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef BOUNDEDPRIORITYQUEUE_H_
#define BOUNDEDPRIORITYQUEUE_H_
#include <boost/heap/fibonacci_heap.hpp>
#include <iostream>
#include <sstream>
#include "JobEvent.h"
#include "Debug.h"

typedef typename boost::heap::fibonacci_heap<JobEventPtr> SortedJobQueue;

class BoundedPriorityQueue {
	bool busy;
protected:
	SortedJobQueue queue;
	virtual std::ostream& toStream(std::ostream& out){
		out << "{"  << std::endl;
		for (SortedJobQueue::ordered_iterator it = this->queue.ordered_begin(); it != this->queue.ordered_end(); ++it){
			JobEventPtr ptr = *it;
			out << (*ptr) << std::endl;
		}
		return(out << "}");
	}
public:
	const long max_size;

	BoundedPriorityQueue(long size) : max_size(size){
		this->busy = false;
	}
	virtual ~BoundedPriorityQueue(){}

	bool is_busy(){
		return this->busy;
	}
	bool is_full(){
		return this->queue.size() >= max_size;
	}

	void enqueue(JobEventPtr e){
		if(!this->is_full()){
			_logl(3,"Enqueuing " << *e);
			e->priorityIndicator = JobEvent::POWER_ESTIMATE;
			this->queue.push(e);
		}
		else{
			_logl(3,"Silently ignoring enqueue request for " << *e);
		}
	}

	JobEventPtr dequeue(){
		JobEventPtr j = this->queue.top();
		_logl(3,"Dequeuing " << *j);
		this->queue.pop();
		return j;
	}

	friend std::ostream& operator<< (std::ostream& out, BoundedPriorityQueue& e);
};

#endif /* BOUNDEDPRIORITYQUEUE_H_ */
