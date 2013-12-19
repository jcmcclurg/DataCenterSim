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
#include "Accumulator.h"

class AccumulatorStatistics {
	std::map<int, AccumulatorPtr > stats;
protected:
	virtual std::ostream& toStream(std::ostream& out){
		return out << "AccumulatorStatistics{"<< std::endl
				<< "   TIME_BETWEEN_REJECTED_JOBS: " << stats[TIME_BETWEEN_REJECTED_JOBS] << std::endl
				<< "   TOTAL_ENERGY: " << stats[TOTAL_ENERGY]  << std::endl
				<< "   LATENCY: " << stats[LATENCY]  << std::endl
				<< "}";
	}
public:
	enum StatisticType{TIME_BETWEEN_REJECTED_JOBS, TOTAL_ENERGY, LATENCY};
	AccumulatorStatistics(){
		stats[TIME_BETWEEN_REJECTED_JOBS] = AccumulatorPtr(new Accumulator());
		stats[TOTAL_ENERGY] = AccumulatorPtr(new Accumulator());
		stats[LATENCY] = AccumulatorPtr(new Accumulator());
	}
	virtual ~AccumulatorStatistics(){

	}
	virtual AccumulatorPtr getAccumulator(StatisticType type){
		return stats[type];
	}

	friend std::ostream& operator<< (std::ostream& out, AccumulatorStatistics& e);
};

#endif /* defined(__DataCenterSim__VectorStatistics__) */
