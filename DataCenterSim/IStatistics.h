//
//  IStatistics.h
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#ifndef __DataCenterSim__IStatistics__
#define __DataCenterSim__IStatistics__

#include <iostream>
#include <boost/shared_ptr.hpp>

class IStatistics {
	
public:
	virtual ~IStatistics(){}
	virtual void add(int type, double statistic) = 0;
	virtual double getMean(int type) = 0;
	virtual double getStddev(int type) = 0;
};

//typedef typename boost::shared_ptr<IStatistics> StatisticsPtr;

#endif /* defined(__DataCenterSim__IStatistics__) */
