#include <stdio.h>
#include <string.h>
#include <mpi.h>

#Author:  Kishan Bhugul
#Date:    28-Nov-2016

int main (int argc, char *argv[]){
	
	int rank;
	int np;
	int tag = 0;
	
	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Comm_size (MPI_COMM_WORLD, &np);
	
	int sizeOfArray = 16;
	int arrayOfNum[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int blockSize = sizeOfArray/np;
	
	
	if (rank == 0){
		
		int i;
		for(i=0;i<sizeOfArray;i++){
			arrayOfNum[i] = i+1;
		}
		//{1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16}
		
		int sum=0;
		
		//Calulating own sum
		for(i=0;i<blockSize;i++){
			sum = sum + arrayOfNum[i];
		}
		printf("Value: %d from Process %d\n", sum, rank);
		for(i=1;i<np;i++){
			int dest = i;
			MPI_Send (&arrayOfNum[i*blockSize], blockSize, MPI_INT, dest, tag, MPI_COMM_WORLD);		
		}
		
		int receivedNum;
		MPI_Status status;
		for(i=1;i<np;i++){
			int src = i;
			MPI_Recv(&receivedNum, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
			sum = sum + receivedNum;
		}
		
		printf ("The Sum is: %d\n", sum);
		
		
	}else{
		
		int received[blockSize];
		
		int src = 0;
		MPI_Status status;
		MPI_Recv(&received, blockSize, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
		
		int i;
		int toSend = 0;
				
		for(i=0;i<blockSize;i++){
			toSend = toSend + received[i];
		}
		printf("Value: %d from Process %d\n", toSend, rank);
		int dest = 0;
		MPI_Send (&toSend, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}
	
	MPI_Finalize ();
	return 0;
}//END main
