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
#include "IStatistics.h"
class PacketArrivalEvent : public IEvent{
	virtual std::ostream& dump(std::ostream& o) {
      return o << "PacketArrivalEvent{time=" << this->time << "}";
   }
	
public:
	PacketArrivalEvent(double t, EventListPtr p, StatisticsPtr s) : IEvent(t, p, s){}
	virtual void processEvent();
};

#endif /* defined(__DataCenterSim__PacketArrivalEvent__) */
