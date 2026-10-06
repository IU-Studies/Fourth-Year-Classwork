#include <stdio.h>
#include <mpi.h>

#define N 1000

int main(int argc, char** argv) {
    int rank, size;
    long long local_sum = 0;
    long long ring_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Determine neighbor ranks in the ring topology
    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    // Divide N integers among the processes
    int chunk = N / size;
    int start = rank * chunk + 1;
    int end = (rank == size - 1) ? N : (rank + 1) * chunk;

    // Calculate local sum
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }

    printf("[Rank %d] assigned range [%d-%d] -> local sum = %lld | (Prev: %d, Next: %d)\n",
           rank, start, end, local_sum, prev, next);
    fflush(stdout);

    // Ring accumulation
    if (rank == 0) {
        // Rank 0 initiates the ring by sending its local sum to Rank 1
        ring_sum = local_sum;
        MPI_Send(&ring_sum, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);

        // Rank 0 receives the fully accumulated total from the last rank in the ring
        MPI_Recv(&ring_sum, 1, MPI_LONG_LONG, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Verification and display
        long long expected = (long long)N * (N + 1) / 2;
        printf("\n================ RING TOPOLOGY RESULT ================\n");
        printf("Total Sum received back at Rank 0: %lld\n", ring_sum);
        printf("Mathematically Expected Sum     : %lld\n", expected);
        if (ring_sum == expected) {
            printf("Status: SUCCESS (Ring traversal verified!)\n");
        }
        printf("======================================================\n");
        fflush(stdout);
    } else {
        // Other ranks receive accumulated sum from prev, add local_sum, then send to next
        MPI_Recv(&ring_sum, 1, MPI_LONG_LONG, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("-> Rank %d received running sum %lld, adding local sum %lld\n", rank, ring_sum, local_sum);
        fflush(stdout);

        ring_sum += local_sum;
        MPI_Send(&ring_sum, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
