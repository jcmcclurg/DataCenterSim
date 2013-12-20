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

PriorityQueueEventList::PriorityQueueEventList(long size,PriorityTypePtr sortOrder) : BoundedPriorityQueue(size) {
	this->sortOrder = sortOrder;
}

bool PriorityQueueEventList::enqueue(EventPtr job){
	*(this->sortOrder) = JobEvent::TIME;
	return BoundedPriorityQueue::enqueue(job);
}
EventPtr PriorityQueueEventList::dequeue(){
	*(this->sortOrder) = JobEvent::TIME;
	return BoundedPriorityQueue::dequeue();
}
