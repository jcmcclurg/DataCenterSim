/*
 * UnitTest.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "UnitTest.h"

#ifdef UNITTEST
#include "AccumulatorStatistics.h"
#include "DataCenterRandom.h"
#include "Debug.h"
#include "Event.h"
#include "JobEvent.h"

void test_accumulator(DataCenterRandomPtr rand, AccumulatorStatistics& stat){
	double l;
	AccumulatorPtr p = stat.getAccumulator(AccumulatorStatistics::LATENCY);
	int i;
	for(i = 0; i < 100; ++i){
		l = rand->sample_arrivalTimeDistribution();
		p->add(l,i);
	}
	_NOTEL(0, stat);
}

void test_working_servers(
		PriorityQueueWorkingServersPtr workingServersQueue,
		PriorityTypePtr sortOrder,
		AccumulatorStatistics& stat){
	JobEventPtr j1(new JobEvent(0, Event::JOB_ARRIVAL, sortOrder));
	j1->powerConsumption = 100;
	JobEventPtr j2(new JobEvent(1, Event::JOB_ARRIVAL, sortOrder));
	j2->powerConsumption = 100;
	JobEventPtr j3(new JobEvent(2, Event::JOB_ARRIVAL, sortOrder));
	j3->powerConsumption = 100;
	JobEventPtr j4(new JobEvent(3, Event::JOB_ARRIVAL, sortOrder));
	j4->powerConsumption = 100;
	JobEventPtr j5(new JobEvent(4, Event::JOB_ARRIVAL, sortOrder));
	j5->powerConsumption = 50;

	workingServersQueue->enqueue(j1,0);
	workingServersQueue->enqueue(j2,2);
	workingServersQueue->enqueue(j3,3);
	workingServersQueue->enqueue(j4,4);

	workingServersQueue->remove(j3,6);

	workingServersQueue->enqueue(j5,5);
	_NOTEL(0,stat);
}

#endif
