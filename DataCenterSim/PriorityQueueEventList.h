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
};

#endif /* defined(__DataCenterSim__PriorityQueueEventList__) */
