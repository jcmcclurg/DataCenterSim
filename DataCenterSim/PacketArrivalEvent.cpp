//
//  PacketArrivalEvent.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include "PacketArrivalEvent.h"
#include "PacketDepartureEvent.h"

void PacketArrivalEvent::processEvent(IEventList& i, IStatistics& s){
    // Dequeue the arrival packet.
    i.dequeue();
    
    // TODO: Schedule the next arrival.

    // Schedule the departure
    PacketDepartureEvent* e = new PacketDepartureEvent(this->time + 1.0);
    i.enqueue(*e);
    printf("Packet arrived at time %f.\n", this->time);
}