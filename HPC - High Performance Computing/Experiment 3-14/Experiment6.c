#include <stdio.h>
#include <omp.h>

int main() {
    int val = 1234;

    printf("Before Parallel Region: val = %d\n\n", val);

    // Set number of threads to 4
    omp_set_num_threads(4);

    // Each thread gets its own private instance of 'val'
    #pragma omp parallel private(val)
    {
        int tid = omp_get_thread_num();

        // Initialize the private variable for each thread
        val = 100 * (tid + 1);

        printf("Thread %d: Initial private val = %d\n", tid, val);

        val += 5; // Modify the private copy

        printf("Thread %d: Updated private val = %d\n", tid, val);
    }

    printf("\nAfter Parallel Region: val = %d (remains unchanged)\n", val);

    return 0;
}
