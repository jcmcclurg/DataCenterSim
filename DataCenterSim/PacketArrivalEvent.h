//
//  PacketArrivalEvent.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__PacketArrivalEvent__
#define __DataCenterSim__PacketArrivalEvent__

#include <iostream>
#include "IEvent.h"
#include "IEventList.h"

class PacketArrivalEvent : public IEvent{

public:
	PacketArrivalEvent(double t) : IEvent(t){}
	virtual void processEvent(IEventList& i, IStatistics& s);
};

#endif /* defined(__DataCenterSim__PacketArrivalEvent__) */
