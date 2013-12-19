/*
 * UnitTest.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "UnitTest.h"

#include "AccumulatorStatistics.h"
#include "DataCenterRandom.h"
#include "Debug.h"

void test_accumulator(DataCenterRandom& rand, AccumulatorStatistics& stat){
	double l;
	AccumulatorPtr p = stat.getAccumulator(AccumulatorStatistics::LATENCY);
	int i;
	for(i = 0; i < 100; ++i){
		l = rand.sample_arrivalTimeDistribution();
		p->add(l);
	}
	_logl(0, *p);
}
