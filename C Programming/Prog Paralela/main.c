//
//  main.c
//  C-Project
//
//  Created by Julio Brazil on 04/08/17.
//  Copyright © 2017 Julio Brazil LTDA. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 9

void ijk(int a[][MAX], int b[][MAX], int c[][MAX], int n){
    int i, j, k;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
}

void ikj(int a[][MAX], int b[][MAX], int c[][MAX], int n){
    int i, j, k;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
}

void ikjBlock(int a[][MAX], int b[][MAX], int c[][MAX], int n){
    int i, j, k, iInner, jInner, kInner, blockSize = 3;

    for(i = 0; i < n; i += blockSize){
        for(k = 0; k < n; k += blockSize){
            for(j = 0; j < n; j += blockSize){
                for (iInner = i; iInner < i+blockSize; iInner++){
                    for (kInner = k ; kInner < k+blockSize; kInner++){
                        for (jInner = j ; jInner < j+blockSize ; jInner++){
                            c[iInner][jInner] += a[iInner][kInner] * b[kInner][jInner];
                        }
                    }
                }
            }
        }
    }
}

int a[MAX][MAX], b[MAX][MAX], rez[MAX][MAX] = {0}, n = MAX, i, j;

int main(int argc, const char * argv[]) {
    srand(0);
    
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            a[i][j] = rand();
            //printf("%d\n",a[i][j]);
        }
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            b[i][j] = rand();
            //printf("%d\n",a[i][j]);
        }
    }

    //the business line
    ikjBlock(a, b, rez, n);

     for(i = 0; i < n; i++){
         for(j = 0; j < n; j++){
             printf("%d ", rez[i][j]);
         }
         printf("\n");
     }

    return 0;
}
