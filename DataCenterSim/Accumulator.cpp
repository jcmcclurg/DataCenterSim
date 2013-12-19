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
