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
	virtual std::ostream& toStream(std::ostream& out){
		return(out << "Event{time="<< this->time << ",type=" << this->type << "}");
	}
public:
	enum EventType { JOB_ARRIVAL, SORTED_QUEUE_READY, JOB_FINISHED, WORKING_SERVERS_QUEUE_READY };

	double time;
	Event::EventType type;

	Event(double t, Event::EventType i){
		this->time = t;
		this->type = i;
	}
	virtual ~Event(){}

	friend std::ostream& operator<< (std::ostream& out, Event& e);
	friend bool operator< (Event& a, Event& b);
	friend bool operator== (Event& a, Event& b);
};

typedef typename boost::shared_ptr<Event> EventPtr;

#endif /* defined(__DataCenterSim__Event__) */
