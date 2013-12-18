//
//  PacketArrivalEvent.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include <iostream>
#include "PacketArrivalEvent.h"
#include "PacketDepartureEvent.h"

void PacketArrivalEvent::processEvent(){
#ifdef DEBUG
	std::cout << "Packet arrived at time " << this->time << std::endl;
#endif
	// Dequeue the arrival packet.
	this->eventList->dequeue();
	
	// TODO: Sample from distribution.
	EventPtr nextArrival(new PacketArrivalEvent(this->time + 1.0, this->eventList, this->statistics));
	this->eventList->enqueue(nextArrival);

	// Schedule the departure
	EventPtr e(new PacketDepartureEvent(this->time + 1.0, this->eventList, this->statistics));
	this->eventList->enqueue(e);
}