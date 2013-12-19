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
protected:
	virtual std::ostream& toStream(std::ostream& out){
		return out << "AccumulatorStatistics{"<< std::endl
				<< "   TIME_BETWEEN_REJECTED_JOBS: " << (*(stats[AccumulatorStatistics::TIME_BETWEEN_REJECTED_JOBS])) << std::endl
				<< "   TOTAL_ENERGY: " << (*(stats[AccumulatorStatistics::TOTAL_ENERGY]))  << std::endl
				<< "   LATENCY: " << (*(stats[AccumulatorStatistics::LATENCY]))  << std::endl
				<< "}";
	}
public:
	enum StatisticType{TIME_BETWEEN_REJECTED_JOBS, TOTAL_ENERGY, LATENCY};
	AccumulatorStatistics(){
		stats[AccumulatorStatistics::TIME_BETWEEN_REJECTED_JOBS] = AccumulatorPtr(new Accumulator());
		stats[AccumulatorStatistics::TOTAL_ENERGY] = AccumulatorPtr(new Accumulator());
		stats[AccumulatorStatistics::LATENCY] = AccumulatorPtr(new Accumulator());
	}
	virtual ~AccumulatorStatistics(){

	}
	virtual AccumulatorPtr getAccumulator(StatisticType type){
		return stats[type];
	}

	friend std::ostream& operator<< (std::ostream& out, AccumulatorStatistics& e);
};

typedef typename boost::shared_ptr<AccumulatorStatistics> AccumulatorStatisticsPtr;

#endif /* defined(__DataCenterSim__VectorStatistics__) */
