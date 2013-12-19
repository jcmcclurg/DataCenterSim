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
	virtual std::string name();
	virtual std::ostream& toStream(std::ostream& out);
public:
	const long max_size;

	virtual bool is_busy();
	virtual bool is_full();
	virtual void reset_busy();
	virtual bool enqueue(EventPtr e);

	virtual EventPtr dequeue();

	BoundedPriorityQueue(long size);
	virtual ~BoundedPriorityQueue(){}

	friend std::ostream& operator<< (std::ostream& out, BoundedPriorityQueue& e);
};

#endif /* BOUNDEDPRIORITYQUEUE_H_ */
