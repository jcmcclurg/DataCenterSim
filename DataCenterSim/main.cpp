//
//  main.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "PriorityQueueEventList.h"
#include "PacketArrivalEvent.h"
#include "VectorStatistics.h"

int main(int argc, const char * argv[])
{
	PriorityQueueEventList eventList;
	VectorStatistics statistics;

	PacketArrivalEvent arrival(1.0);

	printf("Hello world.\n");
	eventList.enqueue(arrival);

	IEvent& e = eventList.getMin();
	e.processEvent(eventList, statistics);

	printf("Event size %f\n", eventList.getMin().time);
	return 0;
}
