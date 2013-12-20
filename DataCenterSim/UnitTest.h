/*
 * UnitTest.h
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

#ifdef UNITTEST
#include "DataCenterRandom.h"
#include "AccumulatorStatistics.h"
#include "PriorityQueueWorkingServers.h"
#include "JobEvent.h"

void test_accumulator(DataCenterRandomPtr rand, AccumulatorStatistics& stat);
void test_working_servers(
		PriorityQueueWorkingServersPtr workingServersQueue,
		PriorityTypePtr sortOrder,
		AccumulatorStatistics& stat);
#endif

#endif /* UNITTEST_H_ */
