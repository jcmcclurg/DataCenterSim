//
//  Event.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__Event__
#define __DataCenterSim__Event__

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <sstream>
#include "IStatistics.h"

class IEventList;

class Event {
protected:
	virtual bool lessThan(Event& other){
		return(this->time > other.time);
	}
	virtual bool equals(Event& other){
		return((this->time == other.time) && (this->type == other.type));
	}
	virtual ostream& toStream(std::ostream& out){
		return(out << "Event{time="<< this->time << ",type=" << this->type << "}");
	}
public:
	double time;
	int type;

	Event(double t, int i){
		this->time = t;
		this->type = i;
	}

	friend std::ostream& operator<< (std::ostream& out, Event& e);
	friend bool operator< (Event& a, Event& b);
	friend bool operator== (Event& a, Event& b);
};

typedef typename boost::shared_ptr<Event> EventPtr;

#endif /* defined(__DataCenterSim__Event__) */
