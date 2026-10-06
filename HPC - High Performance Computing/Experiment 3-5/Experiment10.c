#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int send_data[2];
    int recv_data[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process prepares 2 numbers (array elements)
    send_data[0] = rank * 10 + 1;
    send_data[1] = rank * 10 + 2;

    printf("Process %d generated elements: [%d, %d]\n", rank, send_data[0], send_data[1]);
    fflush(stdout);

    if (rank != 0) {
        // Non-root processes send the 2 integers to Root (rank 0)
        MPI_Send(send_data, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        // Root process prints its own numbers first
        printf("\n--- Root Process (Rank 0) Collection ---\n");
        printf("Root's own data (Process 0): [%d, %d]\n", send_data[0], send_data[1]);
        fflush(stdout);

        // Root receives 2 numbers from each non-root process
        for (int i = 1; i < size; i++) {
            MPI_Recv(recv_data, 2, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Root received from Process %d: [%d, %d]\n", i, recv_data[0], recv_data[1]);
            fflush(stdout);
        }
    }

    MPI_Finalize();
    return 0;
}
