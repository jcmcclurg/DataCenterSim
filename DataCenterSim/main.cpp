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
#include <boost/pointer_cast.hpp>
#include "PriorityQueueEventList.h"
#include "AccumulatorStatistics.h"
#include "Debug.h"
#include "JobEvent.h"
#include "DataCenterRandom.h"

#define MAX_TIME 0.01

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
	double seed = 0;

	double power_mean = 300;				// Watts
	double power_stdev = power_mean/10;

	double arrival_rate = 100;				// Jobs per second

	double completion_time_mean = 0.001;	// Seconds
	double completion_time_stdev = completion_time_mean/10;

	double sorting_time_min = completion_time_mean/100;
	double sorting_time_max = sorting_time_min*2;

	double routing_time_min = sorting_time_min;
	double routing_time_max = sorting_time_max;

	DataCenterRandom rand(
			seed,
			power_mean,
			power_stdev,
			arrival_rate,
			completion_time_mean,
			completion_time_stdev,
			sorting_time_min,
			sorting_time_max,
			routing_time_min,
			routing_time_max);

	PriorityQueueEventList eventList;
	AccumulatorStatistics statistics;
	double time = 0;
	
	JobEventPtr arrival(new JobEvent(0, Event::JOB_ARRIVAL));
	
	_logl(0,"Welcome to the data center stacked server simulator.");
	_logl(1,"Initialization parameters: ");
	_logl(1,"Simulation time: " << MAX_TIME);
	_logl(1, rand);

	// Queue up initial arrival.
	eventList.enqueue(arrival);
	
	while(time < MAX_TIME){
		EventPtr e = eventList.getMin();
		eventList.dequeue();
		time = e->time;

		if(e->type == Event::JOB_ARRIVAL || e->type == Event::JOB_FINISHED){
			JobEventPtr d = boost::static_pointer_cast<JobEvent>(e);
			_logl(2,"Processing job event.");
			if(e->type == Event::JOB_ARRIVAL){
				double t = time + rand.sample_arrivalTimeDistribution();
				_logl(2,"Scheduling new job arrival at time " << t);

				JobEventPtr j(new JobEvent(t, Event::JOB_ARRIVAL));
				eventList.enqueue(j);
			}
		}
		else if(e->type == Event::SORTED_QUEUE_READY){
			_logl(2,"Processing sorted queue event.");
		}
		else if(e->type == Event::WORKING_SERVERS_QUEUE_READY){
			_logl(2,"Processing working servers queue event.");
		}
	}
	
	_logl(1,"Finished simulation after " << time << " seconds.");
	return 0;
}
