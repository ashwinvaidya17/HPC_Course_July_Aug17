#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv [])
{
 /*  int rank,size;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   printf("I am %d of %d\n",rank,size);
   MPI_Finalize();
   return 0;
*/
/*   int rank,size;
   int len;
   char hostname[MPI_MAX_PROCESSOR_NAME];
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   MPI_Get_processor_name(hostname,&len);
   printf("I am %d of %d running on %s\n",rank,size,hostname);
   MPI_Finalize();
   return 0;
   */
   int rank,size, rc, numtask,count,tag,dest,source;
   tag=1;
   MPI_Status stat;
   char inmsg[100], outmsg[100]="Hello from Earth";
   char hostname[MPI_MAX_PROCESSOR_NAME];
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   if(rank==0)
   {
     dest=1;
     source=1;
     MPI_Send(&outmsg,17,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
     //MPI_Recv(&inmsg),100,MPI_CHAR,source,tag,MPI_COMM_WORLD,&stat);
   }
      if(rank==1)
   {
     dest=0;
     source=0;
     //MPI_Send(&outmsg,100,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
     MPI_Recv(&inmsg,17,MPI_CHAR,source,tag,MPI_COMM_WORLD,&stat);
     printf("%s\n",inmsg);
   }
   MPI_Finalize();
   return 0;
}
