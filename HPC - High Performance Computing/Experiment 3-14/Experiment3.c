#include <stdio.h>
#include <omp.h>

int main () 
{	
	#pragma omp parallel
	{
	int thread_ID = omp_get_thread_num();
	printf("Hello World the thread ID is: %d\n", thread_ID);
	}
return 0;
}
