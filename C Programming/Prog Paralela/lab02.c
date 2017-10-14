//
//  lab02.c
//  C Programming
//
//  Created by Julio Brazil on 09/09/17.
//  Copyright © 2017 Julio Brazil LTDA. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    pid_t child;
    int *var, shm_id, time = 100000;
    
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);
    if (shm_id < 0) {
        printf("error in shmget");
        return 0;
    }
    var = (int *)shmat(shm_id, NULL, 0);
    *var = 1;
    printf("var começa com %d",*var);
    
    child = fork();
    if (child > 1) {
        wait(&time);
        *var *= 4;
        printf("\no pai faz var * 4");
        printf("\ne no final var = %d",*var);
    }
    else {
        *var += 3;
        printf("\no filho faz var + 3");
    }
    return 1;
}
