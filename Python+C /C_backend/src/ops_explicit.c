#include "ops_explicit.h"
#include "linalg.h"
#include <string.h>

int cs_explicit_op_init(cs_explicit_op *op, int M , int N, const double *A_data){
	if( M<=0 || N<=0 || !op ) return CS_ERR_INVALID_ARG;
	op->M=M;
	op->N=N;
	op->A_data=A_data;
	return CS_OK;
}


int cs_explicit_op_free(cs_explicit_op *op){
	if(!op) return CS_ERR_INVALID_ARG;

	op->A_data=NULL;
	op->M=op->N=0;
	return CS_OK;
}

int cs_explicit_forward(const cs_explicit_op *op, const double *x, double *y){
	if(!op || !op->A_data) return CS_ERR_INVALID_ARG;

	return cs_matvec(op->A_data, op->M, op->N , x, y);
}

int cs_explicit_transpose(const cs_explicit_op *op ,const double *u, double *z){
	if(!op || !op->A_data) return CS_ERR_INVALID_ARG;

	return cs_rmatvec(op->A_data, op->M, op->N, u, z);
}



