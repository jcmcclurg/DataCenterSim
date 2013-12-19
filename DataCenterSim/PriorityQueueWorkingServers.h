/*
 * PriorityQueueWorkingServers.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef PRIORITYQUEUEWORKINGSERVERS_H_
#define PRIORITYQUEUEWORKINGSERVERS_H_
#include "BoundedPriorityQueue.h"

class PriorityQueueWorkingServers : public BoundedPriorityQueue {
protected:
	virtual std::ostream& toStream(std::ostream& out){
		out << "PriorityQueueWorkingServers";
		BoundedPriorityQueue::toStream(out);
		return(out);
	}
public:
	PriorityQueueWorkingServers(long size) : BoundedPriorityQueue(size){
	}
};

#endif /* PRIORITYQUEUEWORKINGSERVERS_H_ */
