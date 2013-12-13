//
//  PacketDepartureEvent.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__PacketDepartureEvent__
#define __DataCenterSim__PacketDepartureEvent__

#include <iostream>
#include "IEvent.h"
#include "IEventList.h"

class PacketDepartureEvent : public IEvent{
protected:
	virtual std::ostream& dump(std::ostream& o) {
      return o << "PacketDepartureEvent{time=" << this->time << "}";
   }
	
public:
	PacketDepartureEvent(double t, EventListPtr p, StatisticsPtr s) : IEvent(t, p, s){
	}
	virtual void processEvent();
};

#endif /* defined(__DataCenterSim__PacketDepartureEvent__) */