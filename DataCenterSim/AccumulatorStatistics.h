//
//  TotalPowerStatistics.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__VectorStatistics__
#define __DataCenterSim__VectorStatistics__

#include <iostream>
#include <map>
#include <vector>
#include "IStatistics.h"

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/shared_ptr.hpp>

typedef typename boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance> > MeanAndVarianceAccumulator;
typedef typename boost::shared_ptr<MeanAndVarianceAccumulator> MeanAndVarianceAccumulatorPtr;

class AccumulatorStatistics : public IStatistics {
	std::map<int, MeanAndVarianceAccumulatorPtr > stats;
	
public:
	virtual void add(int type, double statistic);
	virtual double getMean(int type);
	virtual double getStddev(int type);
};

#endif /* defined(__DataCenterSim__VectorStatistics__) */
