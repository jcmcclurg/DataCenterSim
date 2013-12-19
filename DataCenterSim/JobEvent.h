//
//  Event.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__JobEvent__
#define __DataCenterSim__JobEvent__

#include "Event.h"

class JobEvent : public Event {
protected:
	virtual std::ostream& toStream(std::ostream& out){
		out << "Job";
		Event::toStream(out);
		return(out);
	}

	virtual bool lessThan(JobEvent& other){
		if(this->priorityIndicator == JobEvent::DIFFERENTIAL_CURRENT){
			return((this->topNeighborCurrent + this->bottomNeighborCurrent) < (other.topNeighborCurrent + other.bottomNeighborCurrent));
		}
		else if(this->priorityIndicator == JobEvent::POWER_ESTIMATE){
			return(this->powerConsumption < other.powerConsumption);
		}
		else{ // if(this->priorityIndicator == JobEvent::TIME){
			return(this->time > other.time);
		}
	}
public:
	enum PriorityType {DIFFERENTIAL_CURRENT,POWER_ESTIMATE,TIME};

	const double originalTime;
	double completionTime;
	double powerConsumption;
	double powerConsumptionEstimate;
	PriorityType priorityIndicator;
	double topNeighborCurrent;
	double bottomNeighborCurrent;

	JobEvent(double t, Event::EventType i) : Event(t, i), originalTime(t) {
		this->completionTime = 0;
		this->powerConsumption = 0;
		this->powerConsumptionEstimate = 0;
		this->priorityIndicator = JobEvent::TIME;
		this->topNeighborCurrent = 0;
		this->bottomNeighborCurrent = 0;
	}
};

typedef typename boost::shared_ptr<JobEvent> JobEventPtr;

#endif /* defined(__DataCenterSim__JobEvent__) */
