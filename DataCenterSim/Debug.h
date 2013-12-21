#ifndef __DataCenterSim__Debug__
#define __DataCenterSim__Debug__

#ifdef DEBUG
#define _NOTE(l,x) if(l <= DEBUG) std::cerr << x
#define _NOTEL(l,x) if(l <= DEBUG) std::cerr << std::string(l*3, ' ') << x << std::endl
#define _LOG(l,x) if(l <= DEBUG) std::cout << x
#define _LOGL(l,x) if(l <= DEBUG) std::cout << std::string(l*3, ' ') << x << std::endl
#else
#define _NOTE(l,x) while(0)
#define _NOTEL(l,x) while(0)
#define _LOG(l,x) while(0)
#define _LOGL(l,x) while(0)
#endif

#endif
