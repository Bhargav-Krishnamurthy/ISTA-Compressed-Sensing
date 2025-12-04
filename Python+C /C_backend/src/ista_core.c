#include "ista.h"
#include "linalg.h"
#include "ops_explicit.h"
#include "utils.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

static inline double soft_threshold(double v, double thresh){
	if(v>thresh) return v-thresh;
	if(v< -thresh) return v+thresh;
	return 0.0;
}

int ista_op(const cs_explicit_op *op, const double *y ,double lam, double step , int max_iters, const double *x0, double *x_out){
	if(!op || !y || lam<0.0 || step <=0.0 || max_iters<=0)
		return CS_ERR_INVALID_ARG;

	int M=op->M;
	int N=op->N;

	double *Ax= (double *) cs_malloc(sizeof(double)*M);
	double *grad= (double *) cs_malloc(sizeof(double) * N);

	if(!Ax || !grad){
		cs_free(Ax);
		cs_free(grad);
		return CS_ERR_ALLOC;
	}

	if(x0) memcpy(x_out, x0, sizeof(double) *N);
	else for(int j=0;j<N;j++) x_out[j]=0.0;

	for(int it=0;it<max_iters;it++){
		int rc= cs_explicit_forward(op, x_out, Ax);
		if(rc !=CS_OK) {
			cs_free(Ax);
			cs_free(grad);
			return rc;
		}

		// finding r=y-Ax (storing it in x)
		for(int i=0;i<M;i++) Ax[i]= y[i]-Ax[i];

		rc = cs_explicit_transpose(op, Ax, grad);
		if (rc != CS_OK) {
			cs_free(Ax);
			cs_free(grad);
			return rc;
		}

		double thresh=lam*step;
		for(int j=0;j<N;j++){
			double v= x_out[j] + step*grad[j];
			x_out[j]=soft_threshold(v, thresh);
		}
	}

	cs_free(Ax);
	cs_free(grad);
	return CS_OK;
}

int ista_dense(const double *A, int M, int N,const double *y,double lam, double step,int max_iters,const double *x0, double *x_out) {
    if (!A) return CS_ERR_INVALID_ARG;

    cs_explicit_op op;

    int rc = cs_explicit_op_init(&op, M, N, A);
    if (rc != CS_OK) return rc;

    rc = ista_op(&op, y, lam, step, max_iters, x0, x_out);
    cs_explicit_op_free(&op);

    return rc;
}


