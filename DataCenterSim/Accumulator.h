/*
 * Accumulator.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef ACCUMULATOR_H_
#define ACCUMULATOR_H_

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/shared_ptr.hpp>
#include <cmath>
#include "Debug.h"

#include <boost/math/distributions/students_t.hpp>

typedef typename boost::math::students_t StudentTDistribution;

typedef typename boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance> > MeanAndVarianceAccumulator;
typedef typename boost::shared_ptr<MeanAndVarianceAccumulator> MeanAndVarianceAccumulatorPtr;

class Accumulator {
	MeanAndVarianceAccumulator accumulator;

protected:
	virtual std::ostream& toStream(std::ostream& out);

public:
	Accumulator() {
	}

	virtual ~Accumulator() {
	}

	virtual void add(double statistic);
	virtual long getN();
	virtual double getCI(double confidence);
	virtual double getMean();
	virtual double getStddev();

	friend std::ostream& operator<< (std::ostream& out, Accumulator& e);
};

typedef typename boost::shared_ptr<Accumulator> AccumulatorPtr;

#endif /* ACCUMULATOR_H_ */
