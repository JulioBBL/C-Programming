//
//  Julio Brazil - 31583784
//  Leonardo Toniolo -
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void exec1(unsigned int *array, unsigned long size, unsigned long chunk) {
    unsigned int sum = 0;

#pragma omp parallel
    {
        for (int i = 0; i < chunk; i++)
        {
#pragma omp critical
            {
                sum += array[(chunk * omp_get_thread_num())+i];
            }
        }
    }
}

void exec2(unsigned int *array, unsigned long size) {
    unsigned int sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
}

int main() {
    unsigned long size = 0x1 << 27;
    clock_t begin, end;

    unsigned int *array = (unsigned int*)calloc(size, sizeof(unsigned int));
    double time1 = 0;
    double time2 = 0;

    int max = omp_get_max_threads();
    unsigned long chunk = size / max;

    printf("max threads: %d - array size: %ld\n", max, size);

    for (int i = 0; i < size; i++) {
        array[i] = 1;
    }

    //1. for paralelo com sessao critica para a soma
    printf("Started algorithm 1\n");
    for (int i = 0; i < 5; i++) {
        printf("%d%%\n", (i*20));
        begin = clock();
        exec1(array,size,chunk);
        end = clock();
        time1 += (double)(end - begin);
    }
    printf("Ended algorithm 1 - %f tics\n", (time1/5));


    //2. for paralelizado e gerenciado pelo OpenMP
    printf("Started algorithm 2\n");
    for (int i = 0; i < 5; i++) {
        printf("%d%%\n", (i*20));
        begin = clock();
        exec2(array,size);
        end = clock();
        time2 += (double)(end - begin);
    }
    printf("Ended algorithm 2 - %f tics\n", (time2/5));

    return 0;
}
