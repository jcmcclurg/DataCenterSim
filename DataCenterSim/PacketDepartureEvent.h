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
    
public:
    PacketDepartureEvent(double t) : IEvent(t){}
    virtual void processEvent(IEventList& i, IStatistics& s);
};

#endif /* defined(__DataCenterSim__PacketDepartureEvent__) */
