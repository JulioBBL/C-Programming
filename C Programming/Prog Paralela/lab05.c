//
//  Julio Brazil - 31583784
//  Leonardo Toniolo -
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

int main() {
    unsigned long size = 0x1 << 27;
    clock_t begin, end;
    
    unsigned long *array = (unsigned long*)calloc(size, sizeof(unsigned long));
    unsigned long sum1 = 0;
    unsigned long sum2 = 0;
    
    int max = omp_get_max_threads();
    unsigned long chunk = size / max;
    unsigned long *tempArray = (unsigned long*)calloc(max, sizeof(unsigned long));
    
    printf("max threads: %d - array size: %ld\n", max, size);
    
    for (int i = 0; i < size; i++) {
        array[i] = 1;
    }
    
    //1. for paralelo com sessao critica para a soma
    begin = clock();
#pragma omp parallel
    {
        for (int i = 0; i < chunk; i++)
        {
#pragma omp critical
            {
                sum1 += array[(chunk * omp_get_thread_num())+i];
            }
        }
    }
    end = clock();
    printf("1. %f tics - sum: %ld\n", (double)(end - begin), sum1);
    
    
    //2. for paralelizado e gerenciado pelo OpenMP
    begin = clock();
#pragma omp parallel for reduction(+ : sum2)
    for (int i = 0; i < size; i++) {
        sum2 += array[i];
    }
    end = clock();
    printf("2. %f tics - sum: %ld\n", (double)(end - begin), sum2);
    
    return 0;
}

