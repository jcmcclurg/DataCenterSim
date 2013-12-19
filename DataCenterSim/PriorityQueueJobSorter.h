/*
 * PriorityQueueJobSorter.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef PRIORITYQUEUEJOBSORTER_H_
#define PRIORITYQUEUEJOBSORTER_H_

#include "BoundedPriorityQueue.h"

class PriorityQueueJobSorter : BoundedPriorityQueue {
protected:
	virtual std::ostream& toStream(std::ostream& out){
		out << "PriorityQueueJobSorter";
		BoundedPriorityQueue::toStream(out);
		return(out);
	}
public:
	PriorityQueueJobSorter(long size) : BoundedPriorityQueue(size){

	}
};

#endif /* PRIORITYQUEUEJOBSORTER_H_ */
