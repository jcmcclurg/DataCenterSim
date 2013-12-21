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
#include <climits>
#include <boost/pointer_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include "PriorityQueueEventList.h"
#include "PriorityQueueJobSorter.h"
#include "PriorityQueueWorkingServers.h"
#include "QueueJobBuffer.h"
#include "AccumulatorStatistics.h"
#include "Debug.h"
#include "JobEvent.h"
#include "DataCenterRandom.h"

#ifdef UNITTEST
#include "UnitTest.h"
#endif

#define MAX_TIME 100
#define EVENT_LIST_LEN LONG_MAX
#define UNSORTED_JOBS_LIST_LEN 100
#define SORTED_JOBS_LIST_LEN UNSORTED_JOBS_LIST_LEN
#define NUM_SERVERS 32

namespace
{
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace
 

// Boilerplate program options code from http://www.radmangames.com/programming/how-to-use-boost-program_options
int main(int argc, char** argv)
{
	double seed = 0;

	double power_mean = 300.0;				// Watts
	double power_stdev = power_mean/10.0;
	double power_estimate_error_stdev = power_stdev/10.0;

	double arrival_rate = 1000.0;				// Jobs per second

	double completion_time_mean = 0.9*NUM_SERVERS/arrival_rate;	// Seconds
	double completion_time_stdev = completion_time_mean/10.0;

	double sorting_time_min = completion_time_mean/1000.0;
	double sorting_time_max = sorting_time_min*2.0;

	double routing_time_min = sorting_time_min;
	double routing_time_max = sorting_time_max;
	try
	{
	/** Define and parse the program options
	*/
	namespace po = boost::program_options;
	po::options_description desc("Options");
	desc.add_options()
	("help", "Print help messages")
	("seed", po::value<double>(&seed), "Seed for random number generator")
	("power_estimate_error_stdev", po::value<double>(&power_estimate_error_stdev), "Power estimate standard deviation")
	("completion_time_stdev", po::value<double>(&completion_time_stdev), "Completion time standard deviation")
	;

	po::variables_map vm;
	try
	{
		po::store(po::parse_command_line(argc, argv, desc),
					vm); // can throw

		/** --help option
		*/
		if ( vm.count("help")  )
		{
			std::cout << "Basic Command Line Parameter App" << std::endl
			<< desc << std::endl;
			return SUCCESS;
		}

		po::notify(vm); // throws on error, so do after help in case
		// there are any problems
	}
	catch(po::error& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
		std::cerr << desc << std::endl;
		return ERROR_IN_COMMAND_LINE;
	}

    // BEGIN APPLICATION CODE //

	DataCenterRandomPtr rand(new DataCenterRandom(
			seed,
			power_mean,
			power_stdev,
			arrival_rate,
			completion_time_mean,
			completion_time_stdev,
			sorting_time_min,
			sorting_time_max,
			routing_time_min,
			routing_time_max,
			power_estimate_error_stdev));

	PriorityTypePtr sortOrder(new JobEvent::PriorityType(JobEvent::TIME));

	PriorityQueueEventListPtr eventList(new PriorityQueueEventList(
			EVENT_LIST_LEN,
			sortOrder));

	AccumulatorStatistics statistics;
	PriorityQueueWorkingServersPtr workingServersQueue(new PriorityQueueWorkingServers(
			NUM_SERVERS,
			rand,
			eventList,
			statistics.getAccumulator(AccumulatorStatistics::LATENCY),
			statistics.getAccumulator(AccumulatorStatistics::TOTAL_ENERGY),
			sortOrder,
			"server_currents.csv"));
	PriorityQueueJobSorterPtr sortedJobQueue(new PriorityQueueJobSorter(
			SORTED_JOBS_LIST_LEN,
			rand,
			workingServersQueue,
			eventList,
			sortOrder));
	QueueJobBufferPtr unsortedJobQueue(new QueueJobBuffer(
			UNSORTED_JOBS_LIST_LEN,
			statistics.getAccumulator(AccumulatorStatistics::TIME_BETWEEN_REJECTED_JOBS),
			sortedJobQueue));


#ifndef UNITTEST
	double time = 0;
	
	JobEventPtr arrival(new JobEvent(0, Event::JOB_ARRIVAL, sortOrder));
	
	_NOTEL(0,"Welcome to the data center stacked server simulator.");
	_LOGL(1,"Initialization parameters: ");
	_LOGL(1,"Simulation time: " << MAX_TIME);
	_LOGL(1,"Event list length: " << EVENT_LIST_LEN);
	_LOGL(1,"Unsorted jobs list length: " << UNSORTED_JOBS_LIST_LEN);
	_LOGL(1,"Sorted jobs list length: " << SORTED_JOBS_LIST_LEN);
	_LOGL(1,"Number of servers: " << NUM_SERVERS);
	_LOGL(1, *rand);

	// Queue up initial arrival.
	_NOTEL(2,"Creating initial arrival event.");
	eventList->enqueue(arrival);
	
	while(time < MAX_TIME){
		EventPtr e = eventList->dequeue();
		time = e->time;
		_NOTEL(2, time);

		if(e->type == Event::JOB_ARRIVAL || e->type == Event::JOB_FINISHED){
			JobEventPtr job = boost::static_pointer_cast<JobEvent>(e);

			if(job->type == Event::JOB_ARRIVAL){
				double t = time + rand->sample_arrivalTime();
				_NOTEL(2,"Processing job arrival event. Scheduling next job arrival for time " << t);
				JobEventPtr nextJob(new JobEvent(t, Event::JOB_ARRIVAL, sortOrder));
				eventList->enqueue(nextJob);

				if(!unsortedJobQueue->enqueue(job)){
					if(!sortedJobQueue->enqueue(job,time)){
						workingServersQueue->enqueue(job,time);
					}
				}
			}

			else{ // if(job->type == Event::JOB_FINISHED){
				_NOTEL(2,"Processing job removal event.");
				workingServersQueue->remove(job,time);
			}
		}

		else if(e->type == Event::SORTED_QUEUE_READY){
			_NOTEL(2,"Processing sorted queue ready event.");
			sortedJobQueue->reset_busy();

			if(!sortedJobQueue->is_empty() && !workingServersQueue->is_busy() && !workingServersQueue->is_full()){
				JobEventPtr job = sortedJobQueue->dequeueJob();
				workingServersQueue->enqueue(job,time);
			}

			if(!unsortedJobQueue->is_empty()){
				JobEventPtr job = unsortedJobQueue->dequeue();
				if(!sortedJobQueue->enqueue(job,time)){
					workingServersQueue->enqueue(job,time);
				}
			}
			else{
				_NOTEL(2,"Nothing for sorted queue to do.");
			}
		}

		else{ // if(e->type == Event::WORKING_SERVERS_QUEUE_READY){
			_NOTEL(2,"Processing working servers queue ready event.");
			workingServersQueue->reset_busy();
			if(!sortedJobQueue->is_busy() && !sortedJobQueue->is_empty()){
				JobEventPtr job = sortedJobQueue->dequeueJob();
				workingServersQueue->enqueue(job,time);
			}
		}
		//_NOTE(3, (*eventList) << std::endl);
	}
	
	_NOTEL(1,"Finished simulation of " << time << " virtual seconds.");
	_LOGL(0,"Simulation results: " << std::endl << statistics);
	return 0;

// Run the Unit tests
#else
	_NOTEL(0,"Welcome to the unit tests.");
	test_accumulator(rand,statistics);
	test_working_servers(workingServersQueue,sortOrder,statistics);
	return 0;
#endif
    // END APPLICATION CODE //

  }
  catch(std::exception& e)
  {
    std::cerr << "Unhandled Exception reached the top of main: "
              << e.what() << ", application will now exit" << std::endl;
    return ERROR_UNHANDLED_EXCEPTION;

  }

  return SUCCESS;

} // main
