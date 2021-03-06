/*
 * Accumulator.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "Accumulator.h"
#include <fstream>
#include <string>

std::ostream& operator<< (std::ostream& out, Accumulator& e){
	return e.toStream(out);
}

Accumulator::~Accumulator() {
	this->accumulatorFile.close();
}

Accumulator::Accumulator(std::string name) {
	this->name = name;
	_NOTEL(4,"Opening accumulator file " << name );
	(this->accumulatorFile).open(name.c_str());
}

std::ostream& Accumulator::toStream(std::ostream& out){
	if(this->getN() > 1){
		return (out << "Accumulator{"
				<< "N=" << this->getN()
				<<",mean=" << this->getMean()
				<< ",std=" << this->getStddev()
				<< ",CI(95%)=" << this->getCI(0.95)
				<< "}");
	}
	else{
		return(out << "Accumulator{N=" << this->getN() << "}");
	}
}
void Accumulator::add(double statistic, double time){
	(this->accumulatorFile) << time << "," << statistic << std::endl;
	_NOTEL(4,"Accumulating " << statistic);
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
