//-------------Ashwin Vaidya----------------------
//-----------------TE 1---------------------------
//----------------302098--------------------------
// Use scatter and gather to add array of size 100.

#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv [])
{
	MPI_Init(&argc, &argv);
	//array is original array and local_array contains array sent via scatter
	int rank, size,array[100],local_array[25];
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//Create an array with numbers 1 to 100
	if(rank==0)
	{
		for (int i = 0; i < 100; ++i)
			{
				array[i]=i+1;
			}
	}
	MPI_Scatter(array,25,MPI_INT,local_array,25,MPI_INT,0,MPI_COMM_WORLD);
	int local_sum=0;
	for (int i = 0; i < 25; ++i)
	{
		local_sum+=local_array[i];
	}
	printf("Partial Sum is %d: %d\n",rank,local_sum);
	//array to store sum from each thread
	int partial_sum[4];
	MPI_Gather(&local_sum,1,MPI_INT,partial_sum,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		int result =0;
		for(int i=0;i<4;i++)
			result += partial_sum[i];
		printf("Sum is: %d\n",result);
	}

	MPI_Finalize();
	return 0;
}
