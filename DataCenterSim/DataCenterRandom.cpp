#include "DataCenterRandom.h"

std::ostream& operator<< (std::ostream& out, DataCenterRandom& e){
	return e.toStream(out);
}
