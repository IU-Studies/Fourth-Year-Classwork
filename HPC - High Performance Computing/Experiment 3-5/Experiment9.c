#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MSG_LEN 100

int main(int argc, char** argv) {
    int rank, size;
    char message[MSG_LEN];

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get current process rank and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 1. Each process prints Hello World locally
    printf("Process %d out of %d says: Hello World!\n", rank, size);

    if (rank != 0) {
        // Non-root processes send a message to Root (rank 0)
        sprintf(message, "Hello World from Process %d!", rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        // Root process (rank 0) receives messages from all other processes
        printf("\n--- Root Process (Rank 0) receiving messages ---\n");
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, MSG_LEN, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Root received: \"%s\"\n", message);
        }
    }

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
