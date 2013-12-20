/*
 * DataCenterRandom.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef DATACENTERRANDOM_H_
#define DATACENTERRANDOM_H_

#include <iostream>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_real_distribution.hpp>

typedef typename boost::mt19937                     PseudoRandom;    // Mersenne Twister
typedef typename boost::random::normal_distribution<double> NormalDistribution;
typedef typename boost::random::variate_generator<PseudoRandom, NormalDistribution> NormalGenerator;    // Variate generator

typedef typename boost::random::exponential_distribution<double> ExponentialDistribution;
typedef typename boost::random::variate_generator<PseudoRandom, ExponentialDistribution> ExponentialGenerator;

typedef typename boost::random::uniform_real_distribution<double> UniformDistribution;
typedef typename boost::random::variate_generator<PseudoRandom, UniformDistribution> UniformGenerator;

class DataCenterRandom {
	double seed;
	const PseudoRandom  randomNumberStream;

	const NormalDistribution powerDistribution;
	const NormalDistribution completionTimeDistribution;
	const NormalDistribution powerEstimationErrorDistribution;

	const ExponentialDistribution arrivalTimeDistribution;
	const UniformDistribution jobSortingTimeDistribution;
	const UniformDistribution jobRoutingTimeDistribution;

	NormalGenerator sample_powerEstimationErrorDistribution;
	NormalGenerator sample_powerDistribution;
	NormalGenerator sample_completionTimeDistribution;

	ExponentialGenerator sample_arrivalTimeDistribution;
	UniformGenerator sample_jobSortingTimeDistribution;
	UniformGenerator sample_jobRoutingTimeDistribution;
protected:
	virtual std::ostream& toStream(std::ostream& out);

public:

	DataCenterRandom(
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

			double powerEstimationErrorStdev);

	virtual ~DataCenterRandom(){
	}

	double sample_arrivalTime();
	double sample_jobSortingTime();
	double sample_jobRoutingTime();
	double sample_power();
	double sample_completionTime();
	double sample_powerEstimate(double actualPower);

	friend std::ostream& operator<< (std::ostream& out, DataCenterRandom& e);
};

typedef typename boost::shared_ptr<DataCenterRandom> DataCenterRandomPtr;

#endif /* DATACENTERRANDOM_H_ */
