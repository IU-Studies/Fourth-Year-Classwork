#include <stdio.h>
#include <omp.h>

int main () 
{
	int temp = 1;
	omp_set_num_threads(4);
	printf("Starting value is: %d\n", temp);
	#pragma omp parallel firstprivate(temp)
	{
		int thread_ID = omp_get_thread_num();
		printf("First Print, value: %d, thread_id: %d\n", temp, thread_ID);
		temp = temp + 1;
		printf("Second Print, value: %d, thread_id: %d\n", temp, thread_ID);
	}
	printf("Third Print, value: %d\n", temp);
	return 0;
}
