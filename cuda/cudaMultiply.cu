#include <stdio.h>
#define _size 512
__global__ void mul(int *a, int *b, int *c)
{
	c[threadIdx.x + blockIdx.x*blockDim.x] = a[threadIdx.x + blockIdx.x*blockDim.x]*b[threadIdx.x + blockIdx.x*blockDim.x];
}

int main()
{
	int SIZE = _size*sizeof(int);
	int *a,*b,*c;
	int *d_a,*d_b,*d_c;
	a = (int *)malloc(SIZE);
	b = (int *)malloc(SIZE);
	c = (int *)malloc(SIZE);
	cudaMalloc((void **)&d_a,SIZE);
	cudaMalloc((void **)&d_b,SIZE);
	cudaMalloc((void **)&d_c,SIZE);
	printf("Enter value of A :\n");
	for(int i=0;i<_size;i++)
	{
			a[i]=i*2;
			//printf("a[%d]\t",i);
			//scanf("%d",&a[i]);
	}
	for(int i=0;i<_size;i++)
	{
			b[i]=i*2+12;
			//printf("b[%d]\t",i);
			//scanf("%d",&b[i]);
	}
		for(int i=0;i<_size;i++)
	{

			printf("a[%d]: %d\tb[%d]: %d\t",i,a[i],i,b[i]);
	}
		printf("\n");
	cudaMemcpy(d_a,a,SIZE,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,SIZE,cudaMemcpyHostToDevice);
	mul<<<2,256>>>(d_a,d_b,d_c);
	cudaThreadSynchronize();
	cudaMemcpy(c,d_c,SIZE,cudaMemcpyDeviceToHost);
	printf("\n");
	for(int i=0;i<_size;i++)
	{

			printf("c[%d]: %d\t",i,c[i]);
	}
	return 0;
}
