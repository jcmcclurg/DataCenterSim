#include <iostream>
#include <functional>
#include "Event.h"

long Event::identifier = 0;

std::ostream& operator<< (std::ostream& out, Event& e){
	return e.toStream(out);
}

bool operator< (Event& a, Event& b){
	return a.lessThan(b);
}

bool operator< (EventPtr a, EventPtr b){
	return a->lessThan(*b);
}

bool operator== (Event& a, Event& b){
	return a.equals(b);
}
