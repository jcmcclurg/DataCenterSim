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

	virtual void remove(EventPtr e){
		typedef typename SortedEventQueue::handle_type handle_t;

		_logl(3,"Trying to remove element " << *e);

		for (SortedEventQueue::iterator it = this->queue.begin(); it != this->queue.end(); ++it){
			EventPtr ptr = *it;
			if(*ptr == *e){
				_log(3,std::cout << "Removing element " << *ptr);

				handle_t h = SortedEventQueue::s_handle_from_iterator(it);
				this->queue.erase(h);
			}
		}
	}
};

#endif /* PRIORITYQUEUEWORKINGSERVERS_H_ */
