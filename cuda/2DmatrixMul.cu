#include <stdio.h>
#include <stdlib.h>

#define _size 3	//Define size of matrix to be 3 by 3;
//__shared__ int result[_size*_size];
__global__ void multiply(int *result, int *A, int *B)
{
	/* OLD logic
	We have a 3 by 3 grid and each block has 3 threads.
	So rows = block x id, cols = block y id
	So Indices will be C[block X id][block Y id] = A[block X id][threads 0, 1, 2] * B[threads 0, 1, 2][block y id]
	*/
	//__shared__ int result[_size*_size] ;
	/*result[blockIdx.x*blockDim.x +blockIdx.y] += A[blockIdx.x*blockDim.x + threadIdx.x]*B[blockDim.x*threadIdx.x+blockIdx.y];
	printf("C[%d] = A[%d]*B[%d] = %d*%d\n",blockIdx.x*blockDim.x +blockIdx.y, blockIdx.x*blockDim.x + threadIdx.x, blockDim.x*threadIdx.x+blockIdx.y,
		A[blockIdx.x*blockDim.x + threadIdx.x],B[blockDim.x*threadIdx.x+blockIdx.y]);
	Res[blockIdx.x*blockDim.x +blockIdx.y]= result[blockIdx.x*blockDim.x +blockIdx.y];*/
	
	/* NEW logic
	I have 3 blocks and 3 threads. Each thread calculates entry for each position compared to the old one having each thread multiplying one value.
	So indices will be result[block x id][thread id] = A[block x id][i]* B[i][thread x id] 
	*/

	for(int i=0; i<_size;i++)
	{
		result[blockIdx.x*blockDim.x +threadIdx.x] += A[blockIdx.x*blockDim.x+i]*B[blockDim.x*i+threadIdx.x];
	}
}

int main(int argc, char const *argv[])
{
	int *d_c,*d_a,*d_b;
	int size = _size*sizeof(int)*_size;
	int *a = reinterpret_cast<int*>(malloc(size));
	int *b = reinterpret_cast<int*>(malloc(size));
	//*result = reinterpret_cast<int*>(malloc(size));
	int *c = reinterpret_cast<int*>(malloc(size));
	//Getting Matrix A
	printf("Enter matrix A\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			scanf("%d",&*(a+i*_size+j) );
		}
	}
	//Printing matrix A
	printf("A is: \n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("%d ",*(a+i*_size+j) );
		}
		printf("\n");
	}
	//Gtting matrix B
	printf("Enter matrix B\n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			scanf("%d",&*(b+i*_size+j));
		}
	}
	//Printing matrix B
	printf("B is: \n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("%d ",*(b+i*_size+j) );
		}
		printf("\n");
	}
	memset(c,0,size);
	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_b,size);
	cudaMalloc((void **)&d_c,size);
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_c,c,size,cudaMemcpyHostToDevice);
	multiply<<<_size,_size>>>(d_c,d_a,d_b);
	cudaThreadSynchronize();
	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	printf("C is: \n");
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			printf("%d ",*(c+i*_size+j) );
		}
		printf("\n");
	}
	return 0;
}