#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv [])
{
	MPI_Init(&argc, &argv);
	int rank, size,number;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
	{
		number =-1;
		MPI_Send(&number,1,MPI_INT,1,0,MPI_COMM_WORLD);
	}
	else if(rank==1)
	{
		MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process 1 recieved number %d from process 0\n", number);
	}
	printf("Hello world, I am %d of %d\n",rank,size);
	MPI_Finalize();
	return 0;
}
