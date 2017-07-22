#include <stdio.h>
#include <omp.h>
int main(int argc, char const *argv[])
{
	int N,N1;
	#pragma omp parallel 
	{
		N = omp_get_num_threads();
		N1 = omp_get_num_procs();
		printf("Thread no: %d Processors: %d\n", N,N1);
		printf("I am thread = %d\n",omp_get_thread_num() );
	}
	int sum=0;			//shared for each thread
	#pragma omp parallel private(sum)
	{
		for (int i = 0; i < 10; ++i)
		{
			sum+=i;
		}	
	printf("Normal for sum %d\n", sum);
	}
	sum=0;
	#pragma omp parallel private(N)
	{
		N=0;
		for (int i = omp_get_thread_num()*25; i < (omp_get_thread_num()+1)*25; ++i)
		{
			N+=i;
		}
		sum+=N;
	}
	printf("Sum: %d\n", sum);
	sum=0;
	#pragma omp for
		for (int i = 0; i < 100; ++i)
		{
			sum+=i;
		}
	printf("Sum: %d\n", sum);
	return 0;
}