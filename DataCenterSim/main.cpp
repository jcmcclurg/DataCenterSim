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

#define MAX_TIME 10.0

/*
 1. Job arrives, with type chosen according to distribution. Schedule next job according to distribution.
 2. If "unsorted jobs queue" is full, job is turned away.
 3. Otherwise, job enters "unsorted jobs queue".
 4. Wait until "sorted jobs queue" is no longer busy.
 5. Enter "sorted jobs queue," and mark the queue as busy for O(log(n)) time.
 6. Wait until "available servers" queue is no longer full.
 8. Enter "available servers" queue, and schedule exit time according to distribution.
 9. Collect latency statistics with each exit.
 
 Collect power statistics every time the number of available servers changes.
 */

int main(int argc, const char * argv[]){
	EventListPtr eventList(new PriorityQueueEventList());
	StatisticsPtr statistics(new VectorStatistics());
	double time = 0;
	
	EventPtr arrival(new PacketArrivalEvent(time, eventList, statistics));
	
#ifdef DEBUG
	std::cout << "Initialization parameters: (none yet)" << std::endl;
#endif

	// Queue up initial arrival.
	eventList->enqueue(arrival);
	
	while(time < MAX_TIME){
		EventPtr e = eventList->getMin();
		time = e->time;
		e->processEvent();
	}
	
	std::cout << "Finished simulation after " << time << " seconds." << std::endl;
	return 0;
}