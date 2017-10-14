//
//  Fibonnacci.c
//  C Programming
//
//  Created by Julio Brazil on 15/09/17.
//  Copyright © 2017 Julio Brazil LTDA. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

long seqfib(long *n){
    //long
    if (*n < 1) return 0;
    else if (*n < 2) return 1;
    else return (seqfib(&(*n)-1) + seqfib(&(*n)-2));
}

long parfib(long n){
    long v1, v2;
    pthread_t t0, t1;
    
    v1 = n-1;
    v2 = n-2;
    
    pthread_create(&t0, NULL, (void*)&seqfib, (void *)&v1);
    pthread_create(&t1, NULL, (void*)&seqfib, (void *)&v2);
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    
    return v1 + v2;
}

int main() {
    long r1 = 0, r2 = 0, fibvalue = 5;
    double t1, t2;
    clock_t begin, end;
    
    begin = clock();
    r1 = seqfib(&fibvalue);
    end = clock();
    t1 = (double)(end - begin) / CLOCKS_PER_SEC;
    
    begin = clock();
    r2 = parfib(fibvalue);
    end = clock();
    t2 = (double)(end - begin) / CLOCKS_PER_SEC;
    
    if (r1 == r2) {
        printf("\nsequencial: %f arbitrary units",t1);
        printf("\nparalel: %f arbitrary units",t2);
        return 0;
    }
    else {
        printf("\nr1 = %ld",r1);
        printf("\nr2 = %ld",r2);
    }
    
    exit(-1);
}
