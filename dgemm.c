#define MAT_SIZE 1024
#define OMP_THREADS 16

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <sys/time.h>


// Function to generate the problem matrices
void gen_problem_matrices(double* A, double* B, int size) ;
// Unoptimized reference dgemm using inner product
void dgemm_0(double* A, double* B, double* C, int size) ;
// Optimized dgemm using outer product
void dgemm_1(double* A, double* B, double* C, int size) ;
// Optimized dgemm using outer product + OMP
void dgemm_2(double* A, double* B, double* C, int size) ;

int main()
{
	int i, j, k, size ;
	double *A_mat1, *B_mat1, *C_mat1 ;
	double *A_mat2, *B_mat2, *C_mat2 ;
	double *A_mat3, *B_mat3, *C_mat3 ;
	struct timeval start_time, end_time ;
	double run_time ;
	
	size = MAT_SIZE ;
	
	// Allocate memory
	A_mat1 = (double *) malloc(sizeof(double)*size*size) ;
	B_mat1 = (double *) malloc(sizeof(double)*size*size) ;
	C_mat1 = (double *) malloc(sizeof(double)*size*size) ;
	A_mat2 = (double *) malloc(sizeof(double)*size*size) ;
	B_mat2 = (double *) malloc(sizeof(double)*size*size) ;
	C_mat2 = (double *) malloc(sizeof(double)*size*size) ;
	A_mat3 = (double *) malloc(sizeof(double)*size*size) ;
	B_mat3 = (double *) malloc(sizeof(double)*size*size) ;
	C_mat3 = (double *) malloc(sizeof(double)*size*size) ;
	printf("Memory for matrices allocated.\n");
	
	//gen_problem_matrices(A_mat, B_mat, size) ;
	//printf("Matrices initialized with random values.\n");
	
	// Launch the reference kernel
	printf("Going to launch basic dgemm kernel.\n");
	run_time = 0.0 ;
	gettimeofday(&start_time, NULL);
	dgemm_0(A_mat1, B_mat1, C_mat1, size) ;
	gettimeofday(&end_time, NULL);
	run_time += (end_time.tv_sec + (double) end_time.tv_usec/1000000) - (start_time.tv_sec + (double) start_time.tv_usec/1000000);
	printf("Run time for basic dgemm kernel: %.6e\n", run_time) ;
	
	// Launch the optimized kernels
	printf("Going to launch optimized dgemm kernel.\n");
	run_time = 0.0 ;
	gettimeofday(&start_time, NULL);
	dgemm_0(A_mat2, B_mat2, C_mat2, size) ;
	gettimeofday(&end_time, NULL);
	run_time += (end_time.tv_sec + (double) end_time.tv_usec/1000000) - (start_time.tv_sec + (double) start_time.tv_usec/1000000);
	printf("Run time for optimized dgemm kernel: %.6e\n", run_time) ;
	
	printf("Going to launch multi-threaded dgemm kernel.\n");
	run_time = 0.0 ;
	gettimeofday(&start_time, NULL);
	dgemm_0(A_mat3, B_mat3, C_mat3, size) ;
	gettimeofday(&end_time, NULL);
	run_time += (end_time.tv_sec + (double) end_time.tv_usec/1000000) - (start_time.tv_sec + (double) start_time.tv_usec/1000000);
	printf("Run time for multi-threaded dgemm kernel: %.6e\n", run_time) ;
	
	// Free all the allocated memory
	free(A_mat1) ;
	free(B_mat1) ;
	free(C_mat1) ;
}

// Function to initialize a matrix
void gen_problem_matrices(double* A, double* B, int size)
{
	int i, j, ind ;
	
	srand(time(NULL)) ;
	
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			ind = (i * size) + j ;
			A[ind] = (double)rand() ;
			B[ind] = (double)rand() ;
		}
	}
}

// Unoptimized reference dgemm using inner product
void dgemm_0(double *A, double *B, double *C, int size)
{
	int i,j,k ;
	
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			C[i*size + j] = 0 ;
			for(k=0; k<size; k++)
			{
				C[i * size + j] += A[i * size + k] * B[k * size + j] ;
			}
		}
	}
}

// Optimized dgemm using outer product
void dgemm_1(double* A, double* B, double* C, int size)
{
	register int i,j,k ;
	
	memset((void*)C, 0, size*size*sizeof(double));
	
	for(k=0; k<size; k++)
	{
		for(i=0; i<size; i++)
		{
			for(j=0; j<size; j++)
			{
				C[i * size + j] += A[i * size + k] * B[k * size + j] ;
			}
		}
	}
}

// Optimized dgemm using OMP
void dgemm_2(double* A, double* B, double* C, int size)
{
	register int i, j, k, ind_i, ind_k ;
	
	memset((void*)C, 0, size*size*sizeof(double));
	
	omp_set_num_threads(OMP_THREADS) ;
	
	#pragma omp parallel for private(k, j, ind_i, ind_k)
	for(i=0; i<size; i++)
	{
		ind_i = i*size ;
		for(k=0; k<size; k++)
		{
			ind_k = k*size ;
			for(j=0; j<size; j++)
			{
				C[ind_i + j] += A[ind_i + k] * B[ind_k + j] ;
			}
		}
	}
}

