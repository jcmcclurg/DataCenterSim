//
//  PacketDepartureEvent.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include <stdio.h>
#include "PacketDepartureEvent.h"

void PacketDepartureEvent::processEvent(IEventList& i, IStatistics& s){
	i.dequeue();
	
	printf("Packet departed at time %f.\n", this->time);
}
