//-------------Ashwin Vaidya----------------------
//-----------------TE 1---------------------------
//----------------302098--------------------------
// Use reduce to add array of size 100.

#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv [])
{
	MPI_Init(&argc, &argv);
	int rank,local_array[25];
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//Total array is from 1 to 100
	//local array is initialized according to rank

	for (int i = 0; i < 25; ++i)
		{
			local_array[i]=i+1+rank*25;
		}

	int local_sum=0;
	for (int i = 0; i < 25; ++i)
	{
		local_sum+=local_array[i];
	}
	printf("Local Sum is %d: %d\n",rank,local_sum);
	int global_sum;
	MPI_Reduce(&local_sum, &global_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("Sum is: %d\n",global_sum);
	}

	MPI_Finalize();
	return 0;
}
