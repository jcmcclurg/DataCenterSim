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
#include "Event.h"
#include "Debug.h"

typedef typename boost::heap::fibonacci_heap<EventPtr> SortedEventQueue;

class BoundedPriorityQueue {
protected:
	bool busy;
	SortedEventQueue queue;
	virtual std::string name(){
		return "BoundedPriorityQueue";
	}
	virtual std::ostream& toStream(std::ostream& out){
		out << "{"  << std::endl;
		for (SortedEventQueue::ordered_iterator it = this->queue.ordered_begin(); it != this->queue.ordered_end(); ++it){
			EventPtr ptr = *it;
			out << (*ptr) << std::endl;
		}
		return(out << "}");
	}
public:
	const long max_size;

	virtual bool is_busy(){
		return this->busy;
	}

	virtual bool is_full(){
		return this->queue.size() >= max_size;
	}

	virtual void reset_busy(){
		this->busy = false;
	}

	virtual bool enqueue(EventPtr e){
		if(!this->is_full()){
			this->busy = true;
			_logl(4,this->name() << " enqueueing " << *e);
			this->queue.push(e);
			return true;
		}
		else{
			_logl(4,this->name() << " is full. Denying enqueue request " << *e);
		}
		return false;
	}

	virtual EventPtr dequeue(){
		EventPtr j = this->queue.top();
		_logl(4,this->name() << " dequeuing " << *j);
		this->queue.pop();
		return j;
	}

	BoundedPriorityQueue(long size) : max_size(size){
		this->busy = false;
	}
	virtual ~BoundedPriorityQueue(){}

	friend std::ostream& operator<< (std::ostream& out, BoundedPriorityQueue& e);
};

#endif /* BOUNDEDPRIORITYQUEUE_H_ */
