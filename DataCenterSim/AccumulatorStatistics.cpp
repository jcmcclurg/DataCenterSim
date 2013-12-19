//
//  TotalPowerStatistics.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include "AccumulatorStatistics.h"
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <cmath>

void AccumulatorStatistics::add(int type, double statistic){
	if (stats.count(type) == 0) {
		MeanAndVarianceAccumulatorPtr j(new MeanAndVarianceAccumulator());
		stats[type] = j;
	}
	
	(*(stats[type]))(statistic);
}

double AccumulatorStatistics::getMean(int type){
	return boost::accumulators::mean(*(stats[type]));
}

double AccumulatorStatistics::getStddev(int type){
	double n = boost::accumulators::count(*(stats[type]));
	double correctionFactor = n/(n-1);
	return std::sqrt((double) (correctionFactor*boost::accumulators::variance(*(stats[type]))));
}
