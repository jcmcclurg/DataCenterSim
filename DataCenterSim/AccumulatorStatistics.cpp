//
//  TotalPowerStatistics.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include "AccumulatorStatistics.h"

std::ostream& operator<< (std::ostream& out, AccumulatorStatistics& e){
	return e.toStream(out);
}

std::ostream& AccumulatorStatistics::toStream(std::ostream& out){
	return out << "AccumulatorStatistics{"<< std::endl
			<< "   TIME_BETWEEN_REJECTED_JOBS: " << (*(this->stats[AccumulatorStatistics::TIME_BETWEEN_REJECTED_JOBS])) << std::endl
			<< "   TOTAL_ENERGY: " << (*(this->stats[AccumulatorStatistics::TOTAL_ENERGY]))  << std::endl
			<< "   LATENCY: " << (*(this->stats[AccumulatorStatistics::LATENCY]))  << std::endl
			<< "}";
}

AccumulatorStatistics::AccumulatorStatistics(){
	this->stats[AccumulatorStatistics::TIME_BETWEEN_REJECTED_JOBS] = AccumulatorPtr(new Accumulator("time_between_rejected_jobs.csv"));
	this->stats[AccumulatorStatistics::TOTAL_ENERGY] = AccumulatorPtr(new Accumulator("total_energy.csv"));
	this->stats[AccumulatorStatistics::LATENCY] = AccumulatorPtr(new Accumulator("latency.csv"));
}

AccumulatorPtr AccumulatorStatistics::getAccumulator(StatisticType type){
	return this->stats[type];
}
