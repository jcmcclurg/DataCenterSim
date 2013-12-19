/*
 * QueueJobBuffer.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "QueueJobBuffer.h"

std::ostream& operator<< (std::ostream& out, QueueJobBuffer& e){
	return e.toStream(out);
}
