#include <iostream>
// complex algorithm for evaluation
void matrix_mult(double *A, double *B, double *C, int N)
{	
	#define everything 

	#ifdef origin 
   for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			C[i * N + j] = 0;
			for (int k = 0; k < N; k++)
			{
				C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	#endif


	#ifdef transpose
		// transpose
	double *tmp = new double[N*N];
		int M = 8;
		for (int k = 0; k < N; k += M)
		{
			for (int p = 0; p < N; p+=M)
			{
				for (int i = k; i < k + M; i++)
				{
					for (int j = p; j < p + M; j++){
						tmp[j * N + i] = B[i * N + j];
						
					}
						
				}
			}
		}

	// for (int i = 0; i < N; i++)
	// {
	// 	for (int j = 0; j < N; j++)
	// 		tmp[j * N + i] = B[i * N + j];
	// }


	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			C[i * N + j] = 0;
			for (int k = 0; k < N; k++)
			{
				C[i*N+j] += A[i*N+k] * tmp[j*N+k];
			}
		}
	#endif

	#ifdef reorder
	for (int i = 0; i < N; i++) {
		int k;
		for ( k = 0; k  < N ; k++) {
			for (int j = 0; j < N; j++) {
				C[i*N + j] += A[i*N+k]*B[k*N + j] ;
			}
		
		}
	
		}

	
	#endif
	#ifdef everything
	//loop reording with loop unrolling 
	double a1,a2,a3,a4,a5,a6,a7,a8;
	int k,j;
	for (int i = 0; i < N; ++i) {
		
		for ( k = 0; k  < (N-7) ; k+=8) {
			
			a1 = A[i*N+k];
			a2 = A[i*N+k+1];
			a3 = A[i*N+k+2];
			a4 = A[i*N+k+3];
			a5 = A[i*N+k+4];
			a6 = A[i*N+k+5];
			a7 = A[i*N+k+6];
			a8 = A[i*N+k+7];
			for ( j = 0; j < N; j++) {
				C[i*N + j] += a1 * B[k*N + j];
				C[i*N + j] += a2 * B[(k+1)*N + j];
				C[i*N + j] += a3 * B[(k+2)*N + j];
				C[i*N + j] += a4 * B[(k+3)*N + j];
				C[i*N + j] += a5 * B[(k+4)*N + j];
				C[i*N + j] += a6 * B[(k+5)*N + j];
				C[i*N + j] += a7 * B[(k+6)*N + j];
				C[i*N + j] += a8 * B[(k+7)*N + j];
			}
		
		}
		if(N % 8) {
			do {
				a1 = A[i*N + k];
				for (int j = 0; j < N; j++) {
					C[i*N + j] += B[k*N + j] * a1;
				}
			}while(++k < N);
		}

	}
	#endif



	
}

