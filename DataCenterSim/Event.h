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
#include "Debug.h"

class Event {
protected:
	static long identifier;
	virtual double toDouble();
	virtual bool lessThan(Event& other);
	virtual bool equals(Event& other);
	virtual std::ostream& toStream(std::ostream& out);
public:
	const long id;
	enum EventType { JOB_ARRIVAL, SORTED_QUEUE_READY, JOB_FINISHED, WORKING_SERVERS_QUEUE_READY };

	double time;
	Event::EventType type;

	Event(double t, Event::EventType i);

	virtual ~Event();

	friend std::ostream& operator<< (std::ostream& out, Event& e);
	friend bool operator< (Event& a, Event& b);
	friend bool operator< (boost::shared_ptr<Event> a, boost::shared_ptr<Event> b);
	friend bool operator== (Event& a, Event& b);
};

typedef typename boost::shared_ptr<Event> EventPtr;

#endif /* defined(__DataCenterSim__Event__) */
