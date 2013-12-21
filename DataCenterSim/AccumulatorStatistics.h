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
#include <boost/shared_ptr.hpp>
#include "Accumulator.h"

class AccumulatorStatistics {
	std::map<int, AccumulatorPtr > stats;
	std::string filename;
protected:
	virtual std::ostream& toStream(std::ostream& out);
public:
	enum StatisticType{TIME_BETWEEN_REJECTED_JOBS, TOTAL_ENERGY, LATENCY};
	AccumulatorStatistics(std::string filename);
	virtual ~AccumulatorStatistics(){
	}
	virtual AccumulatorPtr getAccumulator(StatisticType type);

	friend std::ostream& operator<< (std::ostream& out, AccumulatorStatistics& e);
};

typedef typename boost::shared_ptr<AccumulatorStatistics> AccumulatorStatisticsPtr;

#endif /* defined(__DataCenterSim__VectorStatistics__) */
