//
//  main.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

/*
 0. Initialization:
 	Pick type -> (completionTimeDistribution, powerConsumptionDistribution) mapping.
	Pick job type distribution.
	Pick scaling factor between arrival time and list sorting time. Define amortized list sort/search times.
	First job(type=sample_types()
		originalTime=0,
		time=0,
		completionTime=0,
		powerConsumption=0,
		powerConsumptionEstimate=0,
		priorityIndicator=INDICATOR_TIME,
		topNeighborCurrent=0,
		bottomNeighborCurrent=0,
		) arrives: Event is added to the list.
	Time begins.
 1. On all events: Pop job from event list, set time() = job's time
 2. On job arrival event:
 	2.0. Schedule job arrival event(time = time() + sample_arrivalDistribution(type)).
	2.1. If inputQueue is full: Update statistics for time-between rejectedJobs(type).
	2.2. Else if inputQueue is not empty or sortedQueue is busy or sortedQueue is full: add job to inputQueue.
	2.3. Else if sortedQueue is not empty or workingServersQueue is busy or workingServersQueue is full:
		2.3.1. Change job's priorityIndicator to INDICATOR_POWER_ESTIMATE
		2.3.2. Set powerConsumptionEstimate=sample_powerConsumptionEstimate(type)
		2.3.3. Add job to sortedQueue. Adding the job to sortedQueue sets its state to busy, and schedules a queueSorted event(time=time()+scaling_factor*amortized_insertion_time).
	2.4. Else:
		2.4.0. Update statistics for totalEnergy = (time() - last time total energy was updated)*totalPower
		2.4.1. Change job's priorityIndicator to INDICATOR_DIFFERENTIAL_CURRENT.
		2.4.2. Set powerConsumption=sample_powerConsumption(type)
		2.4.3. Set completionTime=sample_completionTime(type)
		2.4.4. Set workingServersQueue to busy, schedule workingServersQueue sorted event.
		2.4.5. Locate the best match for the job.
		2.4.6. Update topNeighborCurrent and bottomNeighborCurrent for the job and its neighbors
		2.4.7. Schedule a jobFinished event(time=time()+completionTime)
3. On queueSorted event:
	3.1. Set sortedQueue's state to not busy.
	3.2. If inputQueue is not empty, pop job off of inputQueue and do steps 2.3.1 through 2.3.3.
4. On jobFinished event:
	4.1. Update statistics for latency = time() - originalTime
	4.2. Update statistics for totalEnergy = (time() - last time total energy was updated)*totalPower
	4.3. Remove job from workingServersQueue, and update topNeighborCurrent and bottomNeighborCurrent for the job's neighbors.
	4.4. If sortedQueue is not empty or busy
		4.2.1. Locate maximum job from workingServersQueue.
		4.2.2. Locate best match from sortedQueue
		4.2.3. Do steps 2.4.0 through 2.4.7.
5. On workingServersQueue sorted event.
	5.1. Set workingServersQueue state to not busy.
	5.2. If sortedQueue is not empty or busy, do steps 4.2.1 through 4.2.3.
 */
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
