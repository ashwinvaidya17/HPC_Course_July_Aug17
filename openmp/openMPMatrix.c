// Matrix multiplication
#include <stdio.h>
#include "omp.h"
#define _max_size 2
int main(int argc, char const *argv[])
{

	int A[_max_size][_max_size], B[_max_size][_max_size], result[_max_size][_max_size],i,j,k=0;
	printf("Enter values for Matrix A\n");
	for (int i = 0; i < _max_size; ++i)
	{
		for (int j = 0; j < _max_size; ++j)
		{
			printf("A[%d][%d]\n", i,j);
			scanf("%d",&A[i][j]);
		}
	}
	printf("Enter values for Matrix B\n");
	for (int i = 0; i < _max_size; ++i)
	{
		for (int j = 0; j < _max_size; ++j)
		{
			printf("B[%d][%d]\n", i,j);
			scanf("%d",&B[i][j]);
		}
	}
	#pragma omp parallel for
	for (int i = 0; i < _max_size; ++i)
	{
		for (int j = 0; j < _max_size; ++j)
		{
			result[i][j]=0;
		}
	}
	#pragma omp parallel for shared(A,B,result,k) num_threads(_max_size)
		for (i = 0; i < _max_size; ++i)
		{
			for (j = 0; j < _max_size; ++j)
			{
				result[i][k] += A[i][j]*B[j][i];
			}
			k++;
		}
	for (int i = 0; i < _max_size; ++i)
	{
		for (int j = 0; j < _max_size; ++j)
		{
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}
	return 0;
}
