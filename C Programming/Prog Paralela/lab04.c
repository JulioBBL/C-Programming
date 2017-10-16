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

    unsigned long *array1 = (unsigned long*)calloc(size, sizeof(unsigned long));
    unsigned long *array2 = (unsigned long*)calloc(size, sizeof(unsigned long));
    unsigned long *array3 = (unsigned long*)calloc(size, sizeof(unsigned long));
    unsigned long sum1 = 0;
    unsigned long sum2 = 0;
    unsigned long sum3 = 0;

    int max = omp_get_max_threads();
    unsigned long chunk = size / max;
    unsigned long *tempArray = (unsigned long*)calloc(max, sizeof(unsigned long));

    printf("max threads: %d - array size: %ld\n", max, size);

    for (int i = 0; i < size; i++) {
        array1[i] = 1;
        array2[i] = 1;
        array3[i] = 1;
    }

//1. for paralelo com vetor compartilhado para a soma parcial por thread
    begin = clock();
#pragma omp parallel shared(tempArray)
    {
        for (int i = 0; i < chunk; i++)
        {
            tempArray[omp_get_thread_num()] += array1[(chunk * omp_get_thread_num())+i];
        }
    }

    for (int i = 0; i < max; i++) {
        sum1 += tempArray[i];
    }
    end = clock();
    printf("1. %f tics - sum: %ld\n", (double)(end - begin), sum1);

//2. for paralelo com sessao critica para a soma
    begin = clock();
#pragma omp parallel
    {
        for (int i = 0; i < chunk; i++)
        {
#pragma omp critical
            {
                sum2 += array2[(chunk * omp_get_thread_num())+i];
            }
        }
    }
    end = clock();
    printf("2. %f tics - sum: %ld\n", (double)(end - begin), sum2);

//3. for paralelizado e gerenciado pelo OpenMP
    begin = clock();
#pragma omp parallel for reduction(+ : sum3)
      for (int i = 0; i < size; i++) {
          sum3 += array3[i];
      }
    end = clock();
    printf("3. %f tics - sum: %ld\n", (double)(end - begin), sum3);

    return 0;
}
