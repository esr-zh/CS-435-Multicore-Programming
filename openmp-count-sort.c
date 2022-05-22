/*
Parallel version of count sort with OpenMP
by Esrah Zahid (S020289)
using C language
compile: gcc openmp-count-sort.c -fopenmp -lm
run: ./a.out
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int array_size = 10;

void omp_count_sort(int a[], int n)
{
	int i, j, count;
	int *temp = malloc(n*sizeof(int));
	#pragma omp parallel for shared(a, n, temp) private(i, j, count)
		for (i = 0; i < n; i++) {
			count = 0;
			for (j = 0; j < n; j++) {
				if (a[j] < a[i]) {
		       		count++; 
				} else if (a[j] == a[i] && j < i) {
		        		count++; 
				}
        	}
            temp[count] = a[i];
		}
	
	#pragma omp parallel for shared(a, n, temp) private(i)
		for (i = 0; i < n; i++){
			a[i] = temp[i];
        }
	free(temp);
}

int main()
{
	int i, n, *a;

	n = array_size;
	printf("Enter %d elements that you want to sort using omp-count-sort: \n", n);
	a = malloc(n*sizeof(int));
	for (i = 0; i < n; i++){
		scanf("%d", &a[i]);
    }

	double start = omp_get_wtime();
	omp_count_sort(a, n);
	double end = omp_get_wtime();

	printf("Sorted: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\nTime Taken: %f\n", end-start);
	return 0;
}
