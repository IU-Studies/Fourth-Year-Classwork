#include <stdio.h>
#include <omp.h>

int main() {
    // Set number of threads to at least 2
    omp_set_num_threads(2);

    #pragma omp parallel
    {
        #pragma omp sections
        {
            // Section 1: Series of 2
            #pragma omp section
            {
                int tid = omp_get_thread_num();
                printf("--- Series of 2 executed by Thread %d ---\n", tid);
                for (int i = 1; i <= 10; i++) {
                    printf("[Thread %d] 2 x %2d = %2d\n", tid, i, 2 * i);
                }
            }

            // Section 2: Series of 4
            #pragma omp section
            {
                int tid = omp_get_thread_num();
                printf("--- Series of 4 executed by Thread %d ---\n", tid);
                for (int i = 1; i <= 10; i++) {
                    printf("[Thread %d] 4 x %2d = %2d\n", tid, i, 4 * i);
                }
            }
        }
    }

    printf("\nBoth series completed execution by separate threads.\n");
    return 0;
}
