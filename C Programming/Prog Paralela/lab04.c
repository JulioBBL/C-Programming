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
    unsigned long size = 0x1 << 31;
    clock_t begin, end;
    
    int *array1 = (int*)calloc(size, sizeof(int));
    int *array2 = (int*)calloc(size, sizeof(int));
    int *array3 = (int*)calloc(size, sizeof(int));
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    
    for (int i = 0; i < size; i++) {
        array1[i] = i;
        array2[i] = i;
        array3[i] = i;
    }
    
    int max = omp_get_max_threads();
    int chunk = size / max;
    int tempArray[max];
    
    printf("max threads: %d\n", max);
    
    begin = clock();
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        
        for (int i = 0; i < chunk; i++)
        {
            tempArray[thread_id] += array1[(chunk * thread_id)+i];
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
        int thread_id = omp_get_thread_num();
        
        for (int i = 0; i < chunk; i++)
        {
#pragma omp critical
            {
                sum2 += array2[(chunk * thread_id)+i];
            }
        }
    }
    end = clock();
    printf("2. %f tics - sum: %d\n", (double)(end - begin), sum2);
    
    begin = clock();
#pragma omp parallel for private(sum3) reduction(+ : sum3)
    {
        int thread_id = omp_get_thread_num();
        
        for (int i = 0; i < chunk; i++) {
            sum3 += array3[(chunk * thread_id)+i];
        }
    }
    end = clock();
    printf("3. %f tics - sum: %d\n", (double)(end - begin), sum3);
    
    return 0;
}
