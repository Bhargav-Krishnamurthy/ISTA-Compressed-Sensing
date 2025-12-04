#ifndef CS_ISTA_H
#define CS_ISTA_H

#include "types.h"
#include "ops_explicit.h"

#ifdef __cplusplus
extern "C" {
#endif
	CS_API int ista_dense(const double *A, int M , int N, const double *y, double lam, double step ,int max_iters, const double *x0, double *x_out);

	CS_API int ista_op(const cs_explicit_op *op, const double *y ,double lam,double step, int max_iters, const double *x0, double *x_out);


#ifdef __cplusplus
}
#endif

#endif



