//Aim to add C= A+B 10x10 matrix
#include <stdio.h>
#include <omp.h>
#define _size 3
int main(int argc, char const *argv[])
{
	int *A=(int *)malloc(r*c*sizeof(int));
	int *B=(int *)malloc(r*c*sizeof(int));
	int *C=(int *)malloc(r*c*sizeof(int));
	printf("Enter values of A\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("A %d %d:\n",i,j);
			scanf("%d",&*(A+i*_size+j));
		}
	}
	printf("Enter values of B\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("B %d %d:\n",i,j);
			scanf("%d",&*(B+i*_size+j));
		}
	}
	#pragma omp parallel for collapse(2)
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			*(C+i*_size+j) = 0;
			*(C+i*_size+j) = *(A+i*_size+j) + *(B+i*_size+j);
		}
	}
	printf("Value of C\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("%d ",*(C+i*_size+j) );
		}
		printf("\n");
	}
	return 0;
}