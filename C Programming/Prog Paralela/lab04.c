//
//  lab04.c
//  C Programming
//
//  Created by Julio Brazil on 06/10/17.
//  Copyright © 2017 Julio Brazil LTDA. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void setArray(unsigned long* array, unsigned long size){
    for (int i = 0; i < size; i++) {
      array[i] = 1;
    }
}

int main() {
    unsigned long size = 0x1 << 29;
    clock_t begin, end;

    unsigned long *array = (unsigned long*)calloc(size, sizeof(unsigned long));
    unsigned long sum1 = 0;
    unsigned long sum2 = 0;
    unsigned long sum3 = 0;

    int max = omp_get_max_threads();
    unsigned long chunk = size / max;
    unsigned long *tempArray = (unsigned long*)calloc(max, sizeof(unsigned long));

    printf("max threads: %d - array size: %ld\n", max, size);

//1. for paralelo com vetor compartilhado para a soma parcial por thread
    setArray(array, size);
    begin = clock();
#pragma omp parallel shared(tempArray)
    {
        for (int i = 0; i < chunk; i++)
        {
            tempArray[omp_get_thread_num()] += array[(chunk * omp_get_thread_num())+i];
        }
    }

    for (int i = 0; i < max; i++) {
        sum1 += tempArray[i];
    }
    end = clock();
    printf("1. %f tics - sum: %ld\n", (double)(end - begin), sum1);

//2. for paralelo com sessao critica para a soma
    setArray(array, size);
    begin = clock();
#pragma omp parallel
    {
        for (int i = 0; i < chunk; i++)
        {
#pragma omp critical
            {
                sum2 += array[(chunk * omp_get_thread_num())+i];
            }
        }
    }
    end = clock();
    printf("2. %f tics - sum: %ld\n", (double)(end - begin), sum2);

//3. for paralelizado e gerenciado pelo OpenMP
    setArray(array, size);
    begin = clock();
#pragma omp parallel for reduction(+ : sum3)
      for (int i = 0; i < size; i++) {
          sum3 += array[i];
      }
    end = clock();
    printf("3. %f tics - sum: %ld\n", (double)(end - begin), sum3);

    return 0;
}
