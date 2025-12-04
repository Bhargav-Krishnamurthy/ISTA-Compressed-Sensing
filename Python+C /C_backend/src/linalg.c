#include "linalg.h"
#include "utils.h"
#include <string.h>
#include <math.h>

int cs_matvec(const double *A, int M, int N , const double *x, double *y){
	if(!A || M<=0 || N<=0 || !x || !y) return CS_ERR_INVALID_ARG;
	for(int i=0;i<M;i++){
		const double *Ai= A +(size_t)i*N;
		double s= 0.0;

		for(int j=0;j<N;j++)
			s=Ai[j]*x[j];

		y[i]=s;
	}

	return CS_OK;
}

int cs_rmatvec(const double *A, int M, int N, const double *r, double *z) {
	if(!A || !r || !z || M<=0 || N<=0) return CS_ERR_INVALID_ARG;

	for(int j=0;j<N;j++) z[j]=0.0;

	for(int i=0;i<M;i++) {
		const double *Ai= A+ (size_t)i*N;
		double ri=r[i];

		for(int j=0;j<N;j++) z[i] +=Ai[j] * ri;
	}

	return CS_OK;
}

int cs_estimate_lipschitz(const double *A, int M , int N, double *L_est, int n_iter){
	if ( !A || !L_est || n_iter <=0 || M<=0 || N<=0 ) return CS_ERR_INVALID_ARG;

	double *v = (double *) cs_malloc(sizeof(double) *N);
	double *tmpM= (double *) cs_malloc(sizeof(double) *M);
	double *z= (double * ) cs_malloc(sizeof(double) * N);

	if(!v || !tmpM || !z){
		cs_free(v);
		cs_free(tmpM);
		cs_free(z);
		return CS_ERR_ALLOC;
	}

	//initializing v in randomised manner
	for(int j=0;j<N;j++) v[j]= 1.0/ (double) N;

	double norm;

	for(int it=0;it<n_iter; it++){
		cs_matvec(A, M, N, v, tmpM);
		cs_rmatvec(A, M,N,tmpM, z);

		norm=0.0;
		for(int j=0;j<N;j++) norm+=z[j]*z[j];
		norm=sqrt(norm);

		if(norm== 0.0) break;

		//Normalizing v
		for(int j=0;j<N;j++) v[j]=z[j]/ norm;
	}

	cs_matvec(A, M,N,v,tmpM);
	double val=0.0;
	for(int i=0;i<M;i++) val+= tmpM[i]*tmpM[i];

	*L_est = val;

	cs_free(v);
	cs_free(tmpM);
	cs_free(z);

	return CS_OK;
}


