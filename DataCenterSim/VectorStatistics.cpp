//
//  TotalPowerStatistics.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include "VectorStatistics.h"
#include <math.h>

void VectorStatistics::add(int type, double statistic){
    if (sums.count(type) == 0) {
        sums[type] = statistic;
        std::vector<double> j;
        stats[type] = j;
    }
    else{
        sums[type] += statistic;
    }
    
    stats[type].push_back(statistic);
}

double VectorStatistics::getMean(int type){
       
    return sums[type]/stats[type].size();
}

double VectorStatistics::getStddev(int type){
    int i;
    double sum = 0;
    double mean = this->getMean(type);
    for(i = 0; i < stats[type].size(); i++){
        sum += pow(stats[type][i] - mean,2);
    }
    return sqrt(sum/(stats[type].size() - 1));
}