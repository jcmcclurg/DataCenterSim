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
	const ExponentialDistribution arrivalTimeDistribution;
	const NormalDistribution completionTimeDistribution;
	const UniformDistribution jobSortingTimeDistribution;
	const UniformDistribution jobRoutingTimeDistribution;
	const NormalDistribution powerEstimationErrorDistribution;
	NormalGenerator sample_powerEstimationErrorDistribution;
protected:
	virtual std::ostream& toStream(std::ostream& out){
			return(out << "DataCenterRandom{" << std::endl
					<< "   Seed: " << this->seed << std::endl
					<< "   Power ~ Normal(" << powerDistribution.mean() << "," << powerDistribution.sigma() << ")" << std::endl
					<< "   Completion time ~ Normal(" << completionTimeDistribution.mean() << "," << completionTimeDistribution.sigma() << ")" << std::endl
					<< "   Sorting time ~ Uniform(" << jobSortingTimeDistribution.min() << "," << jobSortingTimeDistribution.max() << ")" << std::endl
					<< "   Routing time ~ Uniform(" << jobRoutingTimeDistribution.min() << "," << jobRoutingTimeDistribution.max() << ")" << std::endl
					<< "   Interarrival time ~ Exponential(" << arrivalTimeDistribution.lambda() << ")" << std::endl
					<< "   Power estimation error ~ Normal(" << powerEstimationErrorDistribution.mean() << "," << powerEstimationErrorDistribution.sigma() << ")" << std::endl
					<< "}");
		}
public:
	NormalGenerator  sample_powerDistribution;
	ExponentialGenerator sample_arrivalTimeDistribution;
	NormalGenerator sample_completionTimeDistribution;
	UniformGenerator sample_jobSortingTimeDistribution;
	UniformGenerator sample_jobRoutingTimeDistribution;

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
		sample_powerEstimationErrorDistribution(randomNumberStream, powerEstimationErrorDistribution){
		this->seed = seed;
	}
	virtual ~DataCenterRandom(){
	};

	double sample_powerEstimate(double actualPower){
		return actualPower + sample_powerEstimationErrorDistribution();
	}

	friend std::ostream& operator<< (std::ostream& out, DataCenterRandom& e);
};

#endif /* DATACENTERRANDOM_H_ */
