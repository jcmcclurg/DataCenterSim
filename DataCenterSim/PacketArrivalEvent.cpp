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

void PacketArrivalEvent::processEvent(IEventList& i, IStatistics& s){
#ifdef DEBUG
	std::cout << "Packet arrived at time " << this->time << std::endl;
#endif
	// Dequeue the arrival packet.
	i.dequeue();
	
	// TODO: Schedule the next arrival.

	// Schedule the departure
	EventPtr e(new PacketDepartureEvent(this->time + 1.0));
	i.enqueue(e);
}
