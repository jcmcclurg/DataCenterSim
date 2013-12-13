#include <iostream>
#include "IEvent.h"

std::ostream& operator<< (std::ostream& out, IEvent& e){
	return e.dump(out);
}

bool operator< (IEvent& a, IEvent& b){
	return a.time > b.time;
}

bool operator== (IEvent& a, IEvent& b){
	return a.time == b.time;
}
