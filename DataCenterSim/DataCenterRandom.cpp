#include "DataCenterRandom.h"

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
			<< "}");
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
	sample_powerEstimationErrorDistribution(randomNumberStream, powerEstimationErrorDistribution){
	this->seed = seed;
}

double DataCenterRandom::sample_powerEstimate(double actualPower){
	return actualPower + this->sample_powerEstimationErrorDistribution();
}
