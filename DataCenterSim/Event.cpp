#include <iostream>
#include "Event.h"

std::ostream& operator<< (std::ostream& out, Event& e){
	return e.toStream(out);
}

bool operator< (Event& a, Event& b){
	return a.lessThan(b);
}

bool operator== (Event& a, Event& b){
	return a.equals(b);
}
