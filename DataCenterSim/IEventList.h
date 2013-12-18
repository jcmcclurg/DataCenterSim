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
<<<<<<< HEAD
#include "Event.h"
=======
#include <boost/shared_ptr.hpp>
#include "IEvent.h"
>>>>>>> 38b9aee14a982d44586f559703963aedd0d916d2

class IEventList{
	
public:
	virtual ~IEventList() {}
	virtual void enqueue(EventPtr e) = 0;
	virtual EventPtr getMin() = 0;
	virtual void dequeue() = 0;
	virtual void remove(EventPtr e) = 0;
};

#endif /* defined(__DataCenterSim__IEventList__) */
