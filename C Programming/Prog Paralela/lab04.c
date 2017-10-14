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

int main() {
    unsigned long size = 0x1 << 16;
    clock_t begin, end;

    int *array1 = (int*)calloc(size, sizeof(int));
    int *array2 = (int*)calloc(size, sizeof(int));
    int *array3 = (int*)calloc(size, sizeof(int));
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;

    for (int i = 0; i < size; i++) {
        array1[i] = i+1;
        array2[i] = i+1;
        array3[i] = i+1;
    }

    int max = omp_get_max_threads();
    int chunk = size / max;
    int tempArray[max];

    printf("max threads: %d - array size: %ld\n", max, size);

    begin = clock();
#pragma omp parallel
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
    printf("1. %f tics - sum: %d\n", (double)(end - begin), sum1);

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
    printf("2. %f tics - sum: %d\n", (double)(end - begin), sum2);

    begin = clock();
#pragma omp parallel for reduction(+ : sum3)
      for (int i = 0; i < chunk; i++) {
          sum3 += array3[(chunk * omp_get_thread_num())+i];
      }
    end = clock();
    printf("3. %f tics - sum: %d\n", (double)(end - begin), sum3);

    return 0;
}
