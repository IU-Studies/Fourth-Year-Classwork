#include <stdio.h>
#include <mpi.h>

#define N 10000

int main(int argc, char** argv) {
    int rank, size;
    long long local_sum = 0;
    long long global_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculate the range of integers for each process
    int chunk = N / size;
    int start = rank * chunk + 1;
    int end = (rank == size - 1) ? N : (rank + 1) * chunk;

    // Compute local sum for the assigned range
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }

    printf("Process %d: summing range [%d to %d] -> local sum = %lld\n", rank, start, end, local_sum);
    fflush(stdout);

    // Combine all local sums at Root (rank 0) using MPI_Reduce
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process prints the final result and verification
    if (rank == 0) {
        long long expected = (long long)N * (N + 1) / 2;
        printf("\n--- Result at Root (Rank 0) ---\n");
        printf("Calculated Parallel Sum of first %d integers = %lld\n", N, global_sum);
        printf("Mathematical Expected Sum [N*(N+1)/2]          = %lld\n", expected);
        if (global_sum == expected) {
            printf("Verification: SUCCESS (Sum matches!)\n");
        }
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}
