/*
 * Accumulator.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "Accumulator.h"

std::ostream& operator<< (std::ostream& out, Accumulator& e){
	return e.toStream(out);
}

std::ostream& Accumulator::toStream(std::ostream& out){
	if(this->getN() > 1){
		return (out << "Accumulator{"
				<< "N=" << this->getN()
				<<",mean=" << this->getMean()
				<< ",std=" << this->getStddev()
				<< ",CI(90%)=" << this->getCI(0.9)
				<< "}");
	}
	else{
		return(out << "Accumulator{N=" << this->getN() << "}");
	}
}
void Accumulator::add(double statistic){
	_logl(4,"Accumulating " << statistic);
	this->accumulator(statistic);
}

long Accumulator::getN(){
	return boost::accumulators::count(this->accumulator);
}

double Accumulator::getCI(double confidence){
	long n = this->getN();
	StudentTDistribution student_t(n -1);
	double alpha = 1 - confidence;
	return -boost::math::quantile(student_t, alpha / 2)*getStddev()/std::sqrt((double) n);
}
double Accumulator::getMean(){
	return boost::accumulators::mean(this->accumulator);
}
double Accumulator::getStddev(){
	double n = this->getN();
	double correctionFactor = n/(n-1);
	return std::sqrt((double) (correctionFactor*boost::accumulators::variance(this->accumulator)));
}
