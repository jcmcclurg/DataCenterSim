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

#include "Event.h"
#include <boost/shared_ptr.hpp>

class IEventList{
	
public:
	virtual ~IEventList() {}
	virtual void enqueue(EventPtr e) = 0;
	virtual EventPtr getMin() = 0;
	virtual void dequeue() = 0;
	virtual void remove(EventPtr e) = 0;
};

typedef typename boost::shared_ptr<IEventList> EventListPtr;

#endif /* defined(__DataCenterSim__IEventList__) */
