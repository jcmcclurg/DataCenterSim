/*
 * PriorityQueueEventList.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: Josiah
 */

#include "PriorityQueueEventList.h"


std::string PriorityQueueEventList::name(){
	return "Event list";
}
std::ostream& PriorityQueueEventList::toStream(std::ostream& out){
	out << "PriorityQueueEventList";
	BoundedPriorityQueue::toStream(out);
	return(out);
}

PriorityQueueEventList::PriorityQueueEventList(long size) : BoundedPriorityQueue(size) {
}
