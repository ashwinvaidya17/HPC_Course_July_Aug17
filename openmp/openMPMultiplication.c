#include <stdio.h>
#include <omp.h>
#define _size 2
int main(int argc, char const *argv[])
{
	int A[_size][_size],B[_size][_size],C[_size][_size];
	printf("Enter value of A\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			C[i][j]=0;
			printf("A %d %d\n",i,j );
			scanf("%d",&A[i][j]);
		}
	}
	printf("Enter value of B\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("B %d %d\n",i,j );
			scanf("%d",&B[i][j]);
		}
	}
	printf("C is\n");
	#pragma omp parallel for collapse(3)
	for (int i = 0; i < _size; ++i)
	{
		
		for (int j = 0; j < _size; ++j)
		{
			for (int k = 0; k < _size; ++k)
			{
				
				C[i][j] += A[i][k]*B[k][j];
			}
		}

	}
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