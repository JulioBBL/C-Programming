//
//  lab01.c
//  C Programming
//
//  Created by Julio Brazil on 25/08/17.
//  Copyright © 2017 Julio Brazil LTDA. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, n;
    if (argc != 2){ /* check for valid number of command-line arguments */
        fprintf(stderr, "Usage: %s processes\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    for (i = 1; i < n; i++)
        if ((childpid = fork()))
            break;
    fprintf(stdout, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);
    return 0;
}


/*
 1:
    nem sempre, mas em sua maioria, aparecerão em ordem
 
 2:
    com stdout os prints apareceram misturados um com o outro, com stderr os prints foram mais ordeiros
*/
