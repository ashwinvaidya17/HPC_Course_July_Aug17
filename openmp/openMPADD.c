//Aim to add C= A+B 10x10 matrix
#include <stdio.h>
#include <omp.h>
#define _size 3
int main(int argc, char const *argv[])
{
	int A[_size][_size],B[_size][_size],C[_size][_size];
	printf("Enter values of A\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("A %d %d:\n",i,j);
			scanf("%d",&A[i][j]);
		}
	}
	printf("Enter values of B\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("B %d %d:\n",i,j);
			scanf("%d",&B[i][j]);
		}
	}
	#pragma omp parallel for collapse(2)
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			C[i][j] = 0;
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	printf("Value of C\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("%d ",C[i][j] );
		}
		printf("\n");
	}
	return 0;
}