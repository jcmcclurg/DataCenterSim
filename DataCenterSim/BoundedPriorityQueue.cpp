/*
 * BoundedPriorityQueue.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "BoundedPriorityQueue.h"

std::ostream& operator<< (std::ostream& out, BoundedPriorityQueue& e){
	return e.toStream(out);
}
