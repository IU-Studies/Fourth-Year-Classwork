#include <stdio.h>
#include <omp.h>

int main () {
	omp_set_num_threads(4);
	#pragma omp parallel
	{
	int thread_ID = omp_get_thread_num();
	printf("Mayur Pagote, and thread id is: %d\n",thread_ID);
	}
return 0;
}

