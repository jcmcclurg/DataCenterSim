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
#include "IEvent.h"

void PriorityQueueEventList::enqueue(EventPtr e){
#ifdef DEBUG
	std::cout << "Enqueueing " << *e << std::endl;
#endif
	this->list.push(e);
}

EventPtr PriorityQueueEventList::getMin(){
#ifdef DEBUG
	std::cout << "Minimum is " << *(this->list.top()) << std::endl;
#endif
	return this->list.top();
}

void PriorityQueueEventList::dequeue(){
#ifdef DEBUG
	std::cout << "Dequeueing " << *(this->list.top()) << std::endl;
#endif
	this->list.pop();
}

void PriorityQueueEventList::remove(EventPtr e){
	//typedef PriorityQueue::handle_type handle_t;
	typedef typename PriorityQueue::handle_type handle_t;
	//typedef boost::heap::priority_queue<EventPtr>::handle_type handle_t;

#ifdef DEBUG
	std::cout << "Trying to remove element " << *e << std::endl;
#endif

	for (PriorityQueue::iterator it = this->list.begin(); it != this->list.end(); ++it){
		EventPtr ptr = *it;
		if(*ptr == *e){
#ifdef DEBUG
			std::cout << "Removing element " << *ptr;
#endif
			handle_t h = PriorityQueue::s_handle_from_iterator(it);
			this->list.erase(h);
		}
	}
}
