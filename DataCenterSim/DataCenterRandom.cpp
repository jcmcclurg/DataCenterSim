#include "DataCenterRandom.h"
#include <cmath>
std::ostream& operator<< (std::ostream& out, DataCenterRandom& e){
	return e.toStream(out);
}

std::ostream& DataCenterRandom::toStream(std::ostream& out){
	return(out << "DataCenterRandom{" << std::endl
			<< "   Seed: " << this->seed << std::endl
			<< "   Power ~ Normal(" << powerDistribution.mean() << "," << powerDistribution.sigma() << ")" << std::endl
			<< "   Completion time ~ Normal(" << completionTimeDistribution.mean() << "," << completionTimeDistribution.sigma() << ")" << std::endl
			<< "   Sorting time ~ Uniform(" << jobSortingTimeDistribution.min() << "," << jobSortingTimeDistribution.max() << ")" << std::endl
			<< "   Routing time ~ Uniform(" << jobRoutingTimeDistribution.min() << "," << jobRoutingTimeDistribution.max() << ")" << std::endl
			<< "   Interarrival time ~ Exponential(" << arrivalTimeDistribution.lambda() << ")" << std::endl
			<< "   Power estimation error ~ Normal(" << powerEstimationErrorDistribution.mean() << "," << powerEstimationErrorDistribution.sigma() << ")" << std::endl
			<< "} "
			<< "," << sample_randomRouting(10)
			<< "," << sample_arrivalTime()
			<< "," << sample_jobSortingTime()
			<< "," << sample_jobRoutingTime()
			<< "," << sample_power()
			<< "," << sample_completionTime()
			<< "," << sample_powerEstimate(10)
			);
}

DataCenterRandom::DataCenterRandom(
		double seed,

		double powerMean,
		double powerStdev,

		double arrivalRate,

		double completionTimeMean,
		double completionTimeStdev,

		double sortingTimeMin,
		double sortingTimeMax,

		double routingTimeMin,
		double routingTimeMax,

		double powerEstimationErrorStdev) :

	randomNumberStream(seed),

	powerDistribution(powerMean,powerStdev),
	sample_powerDistribution(randomNumberStream,powerDistribution),

	arrivalTimeDistribution(arrivalRate),
	sample_arrivalTimeDistribution(randomNumberStream,arrivalTimeDistribution),

	completionTimeDistribution(completionTimeMean,completionTimeStdev),
	sample_completionTimeDistribution(randomNumberStream,completionTimeDistribution),

	jobSortingTimeDistribution(sortingTimeMin,sortingTimeMax),
	sample_jobSortingTimeDistribution(randomNumberStream,jobSortingTimeDistribution),

	jobRoutingTimeDistribution(routingTimeMin,routingTimeMax),
	sample_jobRoutingTimeDistribution(randomNumberStream,jobRoutingTimeDistribution),

	powerEstimationErrorDistribution(0,powerEstimationErrorStdev),
	sample_powerEstimationErrorDistribution(randomNumberStream, powerEstimationErrorDistribution),

	randomRoutingDistribution(0,1),
	sample_randomRoutingDistribution(randomNumberStream,randomRoutingDistribution){
	this->roundUp = true;
	this->seed = seed;
}

long DataCenterRandom::sample_randomRouting(long max){
	if(this->roundUp){
		this->roundUp = false;
		return std::floor((max*((double) (sample_randomRoutingDistribution()))) + 0.5);
	}
	else{
		this->roundUp = true;
		return std::ceil((max*((double) (sample_randomRoutingDistribution()))) - 0.5);
	}
}

double DataCenterRandom::sample_powerEstimate(double actualPower){
	return std::max((double) (actualPower + this->sample_powerEstimationErrorDistribution()),0.0);
}

double DataCenterRandom::sample_arrivalTime(){
	return this->sample_arrivalTimeDistribution();
}

double DataCenterRandom::sample_jobSortingTime(){
	return this->sample_jobSortingTimeDistribution();
}
double DataCenterRandom::sample_jobRoutingTime(){
	return this->sample_jobRoutingTimeDistribution();
}

double DataCenterRandom::sample_power(){
	return std::max((double) (this->sample_powerDistribution()),0.0);
}
double DataCenterRandom::sample_completionTime(){
	return std::max((double) (this->sample_completionTimeDistribution()),0.0);
}
