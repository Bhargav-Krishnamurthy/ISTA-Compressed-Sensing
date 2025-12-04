#ifndef CS_LINALG_H
#define CS_LINALG_H

#include "types.h"

CS_API int cs_matvec(const double *A, int M , int N , const double *x,double *y);

CS_API int cs_rmatvec(const double *A, int M , int N, const double *r,double *z);

CS_API int cs_estimate_lipschitz(const double *A, int M , int N , double *L_est, int n_iter);

#endif
