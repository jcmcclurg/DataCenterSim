//
//  TotalPowerStatistics.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include "AccumulatorStatistics.h"

std::ostream& operator<< (std::ostream& out, AccumulatorStatistics& e){
	return e.toStream(out);
}
