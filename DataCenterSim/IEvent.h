//
//  Event.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__IEvent__
#define __DataCenterSim__IEvent__

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <sstream>
#include "IStatistics.h"
class IEventList;

class IEvent {
	virtual std::ostream& dump(std::ostream& o) {
      return o << "Event{time=" << this->time << "}";
   }
	
public:
	double time;
	IEvent(double t){
		time = t;
	}
	virtual void processEvent(IEventList& i, IStatistics& s) = 0;

	friend std::ostream& operator<< (std::ostream& out, IEvent& e);
	friend bool operator< (IEvent& a, IEvent& b);
	friend bool operator== (IEvent& a, IEvent& b);
};

typedef typename boost::shared_ptr<IEvent> EventPtr;

#endif /* defined(__DataCenterSim__IEvent__) */
