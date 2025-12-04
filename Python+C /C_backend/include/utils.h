#ifndef CS_UTILS_H
#define CS_UTILS_H

#include "types.h"

//allocation

CS_API void * cs_malloc(size_t bytes);

//free 

CS_API void cs_free(void *p);

//error notification 

CS_API const char * cs_strerror(int code);

// Timing 

CS_API double cs_wtime(void);

#endif
