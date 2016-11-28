#include <stdio.h>
#include <string.h>
#include <mpi.h>

//Author:	Kishan Bhugul
//Data:		28-Nov-2016


int main (int argc, char *argv[]) {

	int rank;
	int size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank != 0) {

		char message[1024];
		int dest = 0;
		int tag = 0;

		sprintf(message, "Greetings from process %d", rank);
		MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}else {

		char message[1024];
		int src;
		int tag=0;
		MPI_Status status;
		
		printf("Greetings from process %d\n", rank);

		for(src=1; src<size; src++) {

			MPI_Recv(message, 1024, MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);
			printf("%s\n", message);
		}
	}

	MPI_Finalize();
	return 0;

}
