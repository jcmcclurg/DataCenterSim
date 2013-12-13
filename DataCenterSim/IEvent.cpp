#include <iostream>
#include "IEvent.h"

std::ostream& operator<< (std::ostream& out, IEvent& e){
	out << "Event{time=" << e.time << "}";
	return out;
}

bool operator< (IEvent& a, IEvent& b){
	return a.time > b.time;
}

bool operator== (IEvent& a, IEvent& b){
	return a.time == b.time;
}
