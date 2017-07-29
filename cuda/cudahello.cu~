#include <stdio.h>

__global__ void mykernel(void){
//printf("Inside function\n");
printf("Block id: %d\n",blockIdx.x);
printf("Thread id: %d\n",threadIdx.x);
printf("Global id: %d\n",(threadIdx.x + blockIdx.x*blockDim.x));	//blockDim.x is number of threads in a block
}

int main()
{
	dim3 DimGrid(4,1);
	dim3 DimThread(8,1,1);
	mykernel<<<DimGrid,DimThread>>>();		//Kernel call
	cudaThreadSynchronize();				//Waits for kernel to finish
	printf("Hello world\n");
	return 0;
}
