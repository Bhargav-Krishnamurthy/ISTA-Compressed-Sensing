#ifndef CS_TYPES_H
#define CS_TYPES_H

#include <stddef.h>

// error codes
#define CS_OK    0
#define CS_ERR_ALLOC -1
#define CS_ERR_INVALID_ARG -2
#define CS_ERR_INTERNAL -3

// portability macros
#ifdef _WIN32
   #define CS_API __declspec(dllexport)
#else
   #define CS_API
#endif

typedef struct{
	double re;
	double im;
}cs_complex;

#endif
