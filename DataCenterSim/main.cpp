//
//  main.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <boost/heap/priority_queue.hpp>

#include "PriorityQueueEventList.h"
#include "PacketArrivalEvent.h"
#include "VectorStatistics.h"

int main(int argc, const char * argv[])
{
	boost::heap::priority_queue<int> mq;
	mq.push(1);
	mq.push(-1);
	mq.push(1000);
	mq.push(100);
	mq.push(-2);
	for(boost::heap::priority_queue<int>::const_iterator it = mq.begin(); it != mq.end(); ++it){
		std::cout << *it << std::endl;
	}

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
