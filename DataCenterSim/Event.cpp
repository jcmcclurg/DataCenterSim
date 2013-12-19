#include <iostream>
#include <functional>
#include "Event.h"

long Event::identifier = 0;

std::ostream& operator<< (std::ostream& out, Event& e){
	return e.toStream(out);
}

bool operator< (Event& a, Event& b){
	return a.lessThan(b);
}

bool operator< (EventPtr a, EventPtr b){
	return a->lessThan(*b);
}

bool operator== (Event& a, Event& b){
	return a.equals(b);
}

double Event::toDouble(){
	return -(this->time);
}
bool Event::lessThan(Event& other){
	_logl(5,"Comparing " << this->toDouble() << " against " << other.toDouble());
	return(this->toDouble() < other.toDouble());
}
bool Event::equals(Event& other){
	return((this->toDouble() == other.toDouble()) && (this->type == other.type));
}
std::ostream& Event::toStream(std::ostream& out){
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

Event::Event(double t, Event::EventType i) : id(Event::identifier){
	Event::identifier++;
	this->time = t;
	this->type = i;
}

Event::~Event(){
	Event::identifier--;
}
