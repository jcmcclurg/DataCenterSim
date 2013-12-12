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

class VectorStatistics : public IStatistics {
	std::map<int, double> sums;
	std::map<int, std::vector<double> > stats;
	
public:
	virtual void add(int type, double statistic);
	virtual double getMean(int type);
	virtual double getStddev(int type);
};

#endif /* defined(__DataCenterSim__VectorStatistics__) */
