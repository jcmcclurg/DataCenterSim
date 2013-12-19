//  PriorityQueueEventList.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include <limits>
#include <vector>
#include <iostream>
#include "PriorityQueueEventList.h"
#include "Event.h"
#include "Debug.h"

void PriorityQueueEventList::enqueue(EventPtr e){
	_logl(3,"Enqueueing " << *e << std::endl);
	this->list.push(e);
}

EventPtr PriorityQueueEventList::getMin(){
	_logl(3,"Minimum is " << *(this->list.top()));
	return this->list.top();
}

void PriorityQueueEventList::dequeue(){
	_logl(3,"Dequeueing " << *(this->list.top()));
	this->list.pop();
}

void PriorityQueueEventList::remove(EventPtr e){
	typedef typename PriorityQueue::handle_type handle_t;

	_logl(3,"Trying to remove element " << *e);

	for (PriorityQueue::iterator it = this->list.begin(); it != this->list.end(); ++it){
		EventPtr ptr = *it;
		if(*ptr == *e){
			_log(3,std::cout << "Removing element " << *ptr);

			handle_t h = PriorityQueue::s_handle_from_iterator(it);
			this->list.erase(h);
		}
	}
}
