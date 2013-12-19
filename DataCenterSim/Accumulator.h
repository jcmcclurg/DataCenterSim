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

#include <boost/math/distributions/students_t.hpp>

typedef typename boost::math::students_t StudentTDistribution;

typedef typename boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance> > MeanAndVarianceAccumulator;
typedef typename boost::shared_ptr<MeanAndVarianceAccumulator> MeanAndVarianceAccumulatorPtr;

class Accumulator {
	MeanAndVarianceAccumulator accumulator;
protected:
	virtual std::ostream& toStream(std::ostream& out){
		return (out << "Accumulator{"
				<< "N=" << this->getN()
				<<",mean=" << this->getMean()
				<< ",std=" << this->getStddev()
				<< ",CI(90%)=" << this->getCI(0.9)
				<< "}");
	}
public:
	Accumulator() {
	}
	virtual ~Accumulator() {
	}

	virtual void add(double statistic){
		this->accumulator(statistic);
	}

	virtual long getN(){
		return boost::accumulators::count(this->accumulator);
	}

	virtual double getCI(double confidence){
		long n = this->getN();
		StudentTDistribution student_t(n -1);
		double alpha = 1 - confidence;
		return -boost::math::quantile(student_t, alpha / 2)*getStddev()/std::sqrt((double) n);
	}
	virtual double getMean(){
		return boost::accumulators::mean(this->accumulator);
	}
	virtual double getStddev(){
		double n = this->getN();
		double correctionFactor = n/(n-1);
		return std::sqrt((double) (correctionFactor*boost::accumulators::variance(this->accumulator)));
	}
};

typedef typename boost::shared_ptr<Accumulator> AccumulatorPtr;

#endif /* ACCUMULATOR_H_ */
