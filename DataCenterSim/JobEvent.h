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
#include <boost/shared_ptr.hpp>

class JobEvent : public Event {
public:
	enum PriorityType {DIFFERENTIAL_CURRENT,POWER_ESTIMATE,TIME};

	const double originalTime;
	double completionTime;
	double powerConsumption;
	double powerConsumptionEstimate;
	double stringIndex;
	double topNeighborCurrent;
	double bottomNeighborCurrent;

	JobEvent(double t, Event::EventType i, boost::shared_ptr<JobEvent::PriorityType> sortOrder);

protected:
	boost::shared_ptr<PriorityType> priorityIndicator;
	virtual std::ostream& toStream(std::ostream& out);
	virtual bool equals(Event& other);
	virtual double toDouble();
};

typedef typename boost::shared_ptr<JobEvent> JobEventPtr;
typedef typename boost::shared_ptr<JobEvent::PriorityType> PriorityTypePtr;

#endif /* defined(__DataCenterSim__JobEvent__) */
