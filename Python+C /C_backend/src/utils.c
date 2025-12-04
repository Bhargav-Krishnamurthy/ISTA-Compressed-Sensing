#include <stdio.h>
#include "utils.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

void *cs_malloc(size_t bytes){
	return malloc(bytes);
}

void cs_free(void *p){
	if(p) free(p);
}

const char* cs_strerror(int code){
	switch(code){
		case CS_OK:      return "OK";
		case CS_ERR_ALLOC:  return "Allocation failed";
		case CS_ERR_INVALID_ARG:  return "Invalid Argument";
		case CS_ERR_INTERNAL:  return "Internal error";
		default : return "Unknown error code";
	}
}

double cs_wtime(void){
#if defined(_WIN32)
	return (double)clock()/ (double) CLOCKS_PER_SEC;
#else
	struct timespec ts;
	if (clock_gettime(CLOCK_MONOTONIC, &ts)==0) return (double)ts.tv_nsec*1e-9;
	else return (double)clock()/ (double) CLOCKS_PER_SEC;
#endif
}
