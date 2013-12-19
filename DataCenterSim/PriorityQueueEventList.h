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
#include <vector>
#include <boost/heap/fibonacci_heap.hpp>
#include <boost/shared_ptr.hpp>
#include "Event.h"

typedef typename boost::heap::fibonacci_heap<EventPtr> PriorityQueue;

class PriorityQueueEventList {
	PriorityQueue list;
	
public:
	PriorityQueueEventList() {

	}
	virtual ~PriorityQueueEventList() {

	}
	virtual void enqueue(EventPtr e);
	virtual EventPtr getMin();
	virtual void dequeue();
	virtual void remove(EventPtr e);
};
#endif /* defined(__DataCenterSim__PriorityQueueEventList__) */
