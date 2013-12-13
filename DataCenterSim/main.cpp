//
//  main.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include <iostream>
#include "PriorityQueueEventList.h"
#include "PacketArrivalEvent.h"
#include "VectorStatistics.h"

int main(int argc, const char * argv[]){
	PriorityQueueEventList eventList;
	VectorStatistics statistics;
	
	EventPtr arrival(new PacketArrivalEvent(1.0));
	
	std::cout << "Hello world." << std::endl;
	eventList.enqueue(arrival);
	
	EventPtr e = eventList.getMin();
	e->processEvent(eventList, statistics);
	
	std::cout << "Minimum event " << *(eventList.getMin()) << std::endl;
	return 0;
}
