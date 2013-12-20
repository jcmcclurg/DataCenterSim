/*
 * JobEvent.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "JobEvent.h"

std::ostream& JobEvent::toStream(std::ostream& out){
	out << "Job";
	Event::toStream(out);
	return(out);
}

bool JobEvent::equals(Event& other){
	return this->id == other.id;
}

double JobEvent::toDouble(){
	if(*(this->priorityIndicator) == JobEvent::DIFFERENTIAL_CURRENT){
		return this->topNeighborCurrent + this->bottomNeighborCurrent;
	}
	else if(*(this->priorityIndicator) == JobEvent::POWER_ESTIMATE){
		return this->powerConsumption;
	}
	else{ // if(*(this->priorityIndicator) == JobEvent::TIME){
		return Event::toDouble();
	}
}

JobEvent::JobEvent(double t, Event::EventType i, PriorityTypePtr p) : Event(t, i), originalTime(t) {
	this->priorityIndicator = p;
	this->completionTime = 0;
	this->powerConsumption = 0;
	this->powerConsumptionEstimate = 0;
	this->topNeighborCurrent = 0;
	this->bottomNeighborCurrent = 0;
	this->stringIndex = -1;
}
