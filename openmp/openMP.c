#include <stdio.h>
#include "omp.h"
#include <sys/time.h>

#define ARows 100
#define ACols 50
#define BRows ACols
#define BCols 50
\
void InitMat(double MatA[ARows][ACols],double MatB[ARows][ACols],double MatC[ARows][ACols],double MatD[ARows][ACols])
{
	int i,j;
	#pragma omp parallel for
	for(i=0;i<ACols;i++)
	{
		for (j=0;j<ARows; j++)
		{
			MatA[j][i] = 1;//i+j;
		}
	}
	for(i=0;i<BCols;i++)
	{
		for (j=0;j<BRows; j++)
		{
			MatB[j][i] = 2;//i*j;
		}
	}
	for(i=0;i<BCols;i++)
	{
		for (j=0;j<ARows; j++)
		{
			MatC[j][i] = MatD[j][i] =0;
		}
	}
}
void DispMat(double MatA[ARows][ACols],double MatB[BRows][BCols],double MatC[ARows][BCols],double MatD[ARows][BCols])
{
	int i,j;
	printf("A : \n");
	for(i=0;i<ACols;i++)
	{
		for (j=0;j<ARows; j++)
		{
			printf("%f ",MatA[j][i]);
		}
		printf("\n");
	}
	printf("B : \n");
	for(i=0;i<BCols;i++)
		{
			for (j=0;j<BRows; j++)
			{
				printf("%f ",MatB[j][i]);
			}
			printf("\n");
		}
	printf("C : \n");
		for(i=0;i<BCols;i++)
		{
			for (j=0;j<ARows; j++)
			{
				printf("%.1f ",MatC[j][i]);
			}
			printf("\n");
		}
		printf("D : \n");
		for(i=0;i<BCols;i++)
		{
			for (j=0;j<ARows; j++)
			{
				printf("%f ",MatD[j][i]);
			}
			printf("\n");
		}
}
void NormalMul(double MatA[ARows][ACols],double MatB[BRows][BCols],double MatC[ARows][BCols])
{
	int i,j,k;
	for(i=0;i<ARows;i++)
	{
		for(j=0;j<BCols;j++)
		{
			for(k=0;k<ACols;k++)
			{
				MatC[i][j] += MatA[i][k] * MatB[k][j];
			}
		}
	}
}
void MulMul(double MatA[ARows][ACols],double MatB[BRows][BCols],double MatD[ARows][BCols])
{
	int i,j,k, nthreads,chunk=25;

	#pragma omp parallel shared(MatA,MatB,MatD)
	{
		#pragma omp for private(i,j,k)
			for(i=0;i<ARows;i++)
				{
					for(j=0;j<BCols;j++)
					{
						for(k=0;k<ACols;k++)
						{
							MatD[i][j] += MatA[i][k] * MatB[k][j];
						}
					}
				}
	}

}
void MatchMat(double C[ARows][BCols], double D[ARows][BCols])
{
	int i,j;
	for(i=0; i<ARows;i++)
	{
		for(j=0;j<BCols;j++){
			if(C[i][j]!=D[i][j])
			{
				printf("Not Equal!\n");
				return;
			}
		}
	}
	printf("Equal!\n");
}
int main()
{
	omp_set_num_threads(2);
	struct timeval t0,t1;
	double MatA[ARows][ACols];
	double MatB[BRows][BCols];
	double MatC[ARows][BCols];
	double MatD[ARows][BCols]; //Multithreaded
	InitMat(MatA,MatB,MatC,MatD);
	MatchMat(MatC,MatD);
	gettimeofday(&t0,0);
	NormalMul(MatA,MatB,MatC);
	gettimeofday(&t1,0);
	printf("\nTime taken for C: %ld us\n",(t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec);
	gettimeofday(&t0,0);
	MulMul(MatA,MatB,MatD);
	gettimeofday(&t1,0);
	printf("\nTime taken for D: %ld us\n",(t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec);
	//DispMat(MatA,MatB,MatC,MatD);
	MatchMat(MatC,MatD);
	return 0;
}



