#ifndef __DataCenterSim__Debug__
#define __DataCenterSim__Debug__

#ifdef DEBUG
#define _log(l,x) if(l <= DEBUG) std::cerr << x
#define _logl(l,x) if(l <= DEBUG) std::cerr << x << std::endl

#else
#define _log(l,x)
#define _logl(l,x)
#endif

#endif
