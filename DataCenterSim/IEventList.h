//
//  IEventList.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__IEventList__
#define __DataCenterSim__IEventList__

#include <iostream>
#include "IEvent.h"

class IEventList{
	
public:
	virtual ~IEventList() {}
	virtual void enqueue(IEvent& e) = 0;
	virtual IEvent& getMin() = 0;
	virtual void dequeue() = 0;
	virtual void remove(IEvent& e) = 0;
};

#endif /* defined(__DataCenterSim__IEventList__) */
