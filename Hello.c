#include <stdio.h>
#include <mpi.h>

//Author:	Kishan Bhugul
//Date:		28-Nov-2016

int main(int arc, char *argv[]) {

        int size, myrank;
        MPI_Init(&arc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        printf("From the process %d out of %d, Hello World!\n", myrank, size);
        MPI_Finalize();
}

