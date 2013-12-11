//
//  Event.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__IEvent__
#define __DataCenterSim__IEvent__

#include <iostream>
#include "IStatistics.h"
class IEventList;

class IEvent {
    
public:
    double time;
    IEvent(double t){
        time = t;
    }
    virtual void processEvent(IEventList& i, IStatistics& s) = 0;
};

#endif /* defined(__DataCenterSim__IEvent__) */
