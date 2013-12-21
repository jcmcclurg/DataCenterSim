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


std::string BoundedPriorityQueue::name(){
	return "BoundedPriorityQueue";
}

std::ostream& BoundedPriorityQueue::toStream(std::ostream& out){
	out << "{"  << std::endl;
	for (SortedEventQueue::ordered_iterator it = this->queue.ordered_begin(); it != this->queue.ordered_end(); ++it){
		EventPtr ptr = *it;
		out << (*ptr) << std::endl;
	}
	return(out << "}");
}

bool BoundedPriorityQueue::is_busy(){
	return this->busy;
}

bool BoundedPriorityQueue::is_full(){
	return this->queue.size() >= max_size;
}

void BoundedPriorityQueue::reset_busy(){
	this->busy = false;
}

bool BoundedPriorityQueue::enqueue(EventPtr e){
	if(!this->is_full()){
		this->busy = true;
		_NOTEL(4,this->name() << " enqueueing " << *e);
		this->queue.push(e);
		return true;
	}
	else{
		_NOTEL(4,this->name() << " is full. Denying enqueue request " << *e);
	}
	return false;
}

EventPtr BoundedPriorityQueue::dequeue(){
	EventPtr j = this->queue.top();
	_NOTEL(4,this->name() << " dequeuing " << *j);
	this->queue.pop();
	return j;
}

BoundedPriorityQueue::BoundedPriorityQueue(long size) : max_size(size){
	this->busy = false;
}
