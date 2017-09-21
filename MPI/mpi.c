#include "mpi.h"
#include <stdio.h>

#define ARows 64
#define ACols 16
#define BCols 32
#define MASTER 0
#define FROM_MASTER 1
#define FROM_WROKER 2
int main(int argc, char const *argv[])
{
	int numtasks;
	int taskid;
	int numworkers;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	if(numtasks <2)
	{
		printf("Need at least two MPI tasks \n");
		MPI_Abort(MPI_COMM_WORLD, rc);
		exit(1);
	}
	numworkers = numtasks -1;

	if(taskid == MASTER)
	{
		printf("Started with %d tasks\n",numtasks );
		printf("Initializing arrays\n");
		for (int i = 0; i < ARows; ++i)
		{
			for (int j = 0; j < ACols; ++j)
			{
				a[i][j] = i+j;
			}
		}
		for (int i = 0; i < ACols; ++i)
		{
			for (int j = 0; j < BCols; ++j)
			{
				b[i][j] = i*j;
			}
		}

		averow = ARows / numworkers;
		extra = ARows % numworkers;
		offset = 0;
		mtype = FROM_MASTER;

		for (int dest = 1; dest < numworkers; ++dest)
		{
			
		}
	}


	return 0;
}