#ifndef CS_OPS_EXPLICIT_H
#define CS_OPS_EXPLICIT_H

#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
	int M;
	int N;
	const double *A_data;
}cs_explicit_op;

CS_API int cs_explicit_op_init(cs_explicit_op *op, int M , int N, const double *A_data);

CS_API int cs_explicit_op_free(cs_explicit_op *op);

CS_API int cs_explicit_forward(const cs_explicit_op *op, const double *x, double *y);

CS_API int cs_explicit_transpose(const cs_explicit_op *op, const double *u, double *z);

#ifdef __cplusplus
}
#endif

#endif
