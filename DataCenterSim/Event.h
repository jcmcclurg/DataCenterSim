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
	virtual double toDouble(){
		return -(this->time);
	}
	virtual bool lessThan(Event& other){
		_logl(5,"Comparing " << this->toDouble() << " against " << other.toDouble());
		return(this->toDouble() < other.toDouble());
	}
	virtual bool equals(Event& other){
		return((this->toDouble() == other.toDouble()) && (this->type == other.type));
	}
	virtual std::ostream& toStream(std::ostream& out){
		out << "Event{" << this->id << ",time="<< this->time << ",type=";
		if(this->type == Event::JOB_ARRIVAL){
			out << "JOB_ARRIVAL";
		}
		else if(this->type == Event::SORTED_QUEUE_READY){
			out << "SORTED_QUEUE_READY";
		}
		else if(this->type == Event::JOB_FINISHED){
			out << "JOB_FINISHED";
		}
		else if(this->type == Event::WORKING_SERVERS_QUEUE_READY){
			out << "WORKING_SERVERS_QUEUE_READY";
		}
		return( out << "}");
	}
public:
	const long id;
	enum EventType { JOB_ARRIVAL, SORTED_QUEUE_READY, JOB_FINISHED, WORKING_SERVERS_QUEUE_READY };

	double time;
	Event::EventType type;

	Event(double t, Event::EventType i) : id(Event::identifier){
		Event::identifier++;
		this->time = t;
		this->type = i;
	}

	virtual ~Event(){
		Event::identifier--;
	}

	friend std::ostream& operator<< (std::ostream& out, Event& e);
	friend bool operator< (Event& a, Event& b);
	friend bool operator< (boost::shared_ptr<Event> a, boost::shared_ptr<Event> b);
	friend bool operator== (Event& a, Event& b);
};

typedef typename boost::shared_ptr<Event> EventPtr;

#endif /* defined(__DataCenterSim__Event__) */
