//
//  PriorityQueueEventList.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__PriorityQueueEventList__
#define __DataCenterSim__PriorityQueueEventList__

#include <iostream>
#include "BoundedPriorityQueue.h"
#include "Event.h"
#include "Debug.h"

class PriorityQueueEventList : public BoundedPriorityQueue {
protected:
	virtual std::ostream& toStream(std::ostream& out){
		out << "PriorityQueueEventList";
		BoundedPriorityQueue::toStream(out);
		return(out);
	}
public:
	PriorityQueueEventList(long size) : BoundedPriorityQueue(size) {
	}

	virtual void remove(EventPtr e){
		typedef typename SortedJobQueue::handle_type handle_t;

		_logl(3,"Trying to remove element " << *e);

		for (SortedJobQueue::iterator it = this->queue.begin(); it != this->queue.end(); ++it){
			EventPtr ptr = *it;
			if(*ptr == *e){
				_log(3,std::cout << "Removing element " << *ptr);

				handle_t h = SortedJobQueue::s_handle_from_iterator(it);
				this->queue.erase(h);
			}
		}
	}
};
#endif /* defined(__DataCenterSim__PriorityQueueEventList__) */
