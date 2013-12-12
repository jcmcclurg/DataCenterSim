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
#include "IEventList.h"

class PriorityQueueEventList : public IEventList {
	std::vector<IEvent*> list;
	
public:
	virtual void enqueue(IEvent& e);
	virtual IEvent& getMin();
	virtual void dequeue();
	virtual void remove(IEvent& e);
};
#endif /* defined(__DataCenterSim__PriorityQueueEventList__) */
