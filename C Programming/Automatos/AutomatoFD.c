//
//  Julio Brazil - 31583784
//  Leonardo Toniolo - 31512720
//

#include <stdlib.h>
#include <stdio.h>

int afd(char *palavra) {
    
    q0: if (*palavra == '\0') {
        goto negativo;
    }
    else if (*palavra >= '0' && *palavra <= '9'){
        palavra++;
        goto q2;
    }
    else if (*palavra == '+' || *palavra == '-'){
        palavra++;
        goto q1;
    }
    else {
        goto negativo;
    }
        
        
    q1: if (*palavra == '\0') {
        goto negativo;
    }
    else if (*palavra >= '0' && *palavra <= '9'){
        palavra++;
        goto q2;
    }
    else {
        goto negativo;
    }
        
    
    q2: if (*palavra == '\0') {
        goto positivo;
    }
    else if (*palavra >= '0' && *palavra <= '9'){
        palavra++;
        goto q2;
    }
    else if (*palavra == '.'){
        palavra++;
        goto q3;
    }
    else {
        goto negativo;
    }
        
    
    q3: if (*palavra == '\0') {
        goto positivo;
    }
    else if (*palavra >= '0' && *palavra <= '9'){
        palavra++;
        goto q3;
    }
    else {
        goto negativo;
    }
        
    positivo:return 1;
    negativo:return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2){ /* check for valid number of command-line arguments */
        fprintf(stderr, "Uso: %s 'palavraASerTestada'\n", argv[0]);
        return 1;
    }
    
    if (afd(argv[1])) printf("%s é um palavra válida",argv[1]);
    else printf("%s NÃO é um palavra válida",argv[1]);
    
    return 0;
}
