#include <stdio.h>
#include <omp.h>

#define N 16
#define CHUNK 2

int main() {
    int i;

    // Set number of threads to 4
    omp_set_num_threads(4);

    printf("Executing loop of %d iterations with static scheduling (CHUNK = %d):\n\n", N, CHUNK);

    // Statically distribute loop iterations in chunks of size CHUNK
    #pragma omp parallel for schedule(static, CHUNK) private(i)
    for (i = 0; i < N; i++) {
        int tid = omp_get_thread_num();
        printf("Thread %d executed iteration %d\n", tid, i);
    }

    printf("\nAll iterations completed successfully.\n");
    return 0;
}
