#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MSG_LEN 100

int main(int argc, char** argv) {
    int rank, size;
    char message[MSG_LEN];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process %d out of %d says: Hello World!\n", rank, size);
    fflush(stdout);

    if (rank != 0) {
        sprintf(message, "Hello World from Process %d!", rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        printf("\n--- Root Process (Rank 0) receiving messages ---\n");
        fflush(stdout);
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, MSG_LEN, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Root received: \"%s\"\n", message);
            fflush(stdout);
        }
    }

    MPI_Finalize();
    return 0;
}
