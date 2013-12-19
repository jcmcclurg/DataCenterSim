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

void test_accumulator(DataCenterRandom& rand, AccumulatorStatistics& stat);
#endif

#endif /* UNITTEST_H_ */
