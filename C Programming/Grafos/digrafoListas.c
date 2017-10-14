#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* calloc, exit, free */

typedef struct _TNo{
    int w;
    struct _TNo *prox;
}TNo;
typedef struct{
    int V; // quantidade de vértices
    int A; // quantidade de arcos
    TNo **adj; //lista de adjacencia
}TDigrafo;

// declaracao de funcoes
TDigrafo * Init( int V ); // ok
void insereA( TDigrafo *D, int v, int w); // reescrever
void removeA(TDigrafo *D, int v, int w); // fazer
void show(TDigrafo *D); //ok
void libera(TDigrafo *D); // liberar a lista
int indeg(TDigrafo *D, int v); // fazer
int outdeg(TDigrafo *D, int v); // fazer
void busca(TDigrafo * G );
void Busca_Prof(TDigrafo *D, int *visitado, int s);


void tarefas(TDigrafo *D){
    int i, j, *visitado = (int*) calloc(D->V, sizeof(int));
    for (i = 0; i < D->A; i++) {
        for (j = 0; j < D->A - i; j++) {
            if (visitado[j] == 0 && outdeg(D, i) == 0) {
                visitado[j] = 1;
                printf("%d ",D->adj[j]->w);
            }
        }
    }
}

typedef struct {
    int tamanho;
    int primeiro, ultimo;
    int *dados;
    int nItens;
}TFila;

TFila * initQueue(int t) {
    TFila *f;
    
    f = (TFila *) calloc(1 , sizeof(TFila));
    f->dados = (int *) calloc(t, sizeof(int));
    f->tamanho = t;
    f->primeiro = 0;
    f->ultimo = -1;
    f->nItens = 0;
    
    return f;
}

void push(TFila *f, int v) {
    if(f->ultimo == f->tamanho-1) {
        printf("\nfila Cheia!!\n");
        f->ultimo = -1;
    }
    
    f->ultimo++;
    f->dados[f->ultimo] = v; // insere e incrementa ultimo
    f->nItens++; // mais um item inserido
}

int pop(TFila *f) { // pega o item do inicio da fila
    
    int temp = f->dados[f->primeiro]; // pega o valor e incrementa o primeiro
    f->primeiro++;
    
    if(f->primeiro == f->tamanho) {
        f->primeiro = 0;
    }
    
    f->nItens--;  // um item retirado
    return temp;
}

int isEmpty(TFila *f) { // retorna 1 se a fila vazia
    return (f->nItens==0);
}

int isFull(TFila *f) { // retorna 1 se a fila cheia
    return (f->nItens == f->tamanho);
}

void mostrarFila(TFila *f){
    int i;
    for( i = 0; i < f->tamanho; i++ ){ // vetor de listas
        printf("%d\t", f->dados[i]);
    }
}

void Busca_Larg(TDigrafo *D, int *visitado, int s) {
    int aux;
    visitado[s] = 1;
    TFila *fila = initQueue(D->V);
    
    push(fila, s);
    
    while (!isEmpty(fila)) {
        aux = pop(fila);
        printf(" %d", aux);
        
        TNo *aux = D->adj[s];
        while( aux ){
            if (visitado[aux->w] == 0) {
                visitado[aux->w] = 1;
                push(fila, aux->w);
            }
            aux = aux->prox;
        }
    }
}


int main( void ){
    // Declara uma variavel do tipo TDigrafo
    TDigrafo *digrafo;
    int *visitado;
    
    digrafo = Init( 6 );
    
    insereA(digrafo, 0, 2);
    insereA(digrafo, 0, 3);
    insereA(digrafo, 0, 4);
    insereA(digrafo, 2, 4);
    insereA(digrafo, 2, 1);
    insereA(digrafo, 3, 4);
    insereA(digrafo, 3, 5);
    insereA(digrafo, 4, 5);
    insereA(digrafo, 4, 1);
    insereA(digrafo, 5, 1);
    show(digrafo);
    
    visitado = (int*) calloc(digrafo->V, sizeof(int));
    int s=0, t=0;
    printf("\nvisitando o digrafo:");
    Busca_Prof(digrafo, visitado, s);
    
    if( visitado[t] )
        printf("\nExiste o caminho de s=%d t=%d", s, t);
    else
        printf("\nNao existe o caminho de s=%d t=%d", s, t);
    
    tarefas(digrafo);
    
    libera( digrafo );
    
    return 0;
    
}
/*
 Implementacao da busca em profundidade
 Algoritmo Busca( G )
 Entrada: um digrafo G representado em uma estrutura de dados.
 Saída:  visita todos os vértices do dígrafo em profundidade
 */
void busca(TDigrafo * G ){
    
    //para Cada vértice v de G faça
    //	marque v como não visitado
    int *visitado = (int*) calloc(G->V, sizeof(int));
    int v;
    //para Cada vértice v de G faça
    for( v = 0;  v < G->V; v++){
        // se v não foi visitado então
        if( !visitado[v])
            //Busca-prof( G, v)
            Busca_Prof( G, visitado, v);
        
    }
    
}

/*
 Dados vértices s e t de um digrafo G, decidir se existe ou não um caminho de s a t em G. 
 Em outras palavras, decidir se o vértice t está ao alcance do vértice s em G.
 */
void Busca_Prof(TDigrafo *D, int *visitado, int s){
    TNo *aux;
    
    // marca s como visitado
    visitado[s] = 1;
    
    // imprime o visitado
    printf("%d ",s);
    
    aux =  D->adj[s];
    while( aux ){
        // se aux->w nao foi visitado
        
        if (!visitado[aux->w])//visitado[aux->w] == 0
            // visito ele !
            Busca_Prof(D, visitado, aux->w);
        
        
        aux = aux->prox;
    }
    
}
// Função cria e devolve uma nova estrutura TDigrafo,
// inicializa os atributos da estrutura, 
// cria uma lista de adjacência para V vértices 
TDigrafo * Init( int V ){
    TDigrafo *D;
    int i;
    // aloca uma estrutura do tipo TDigrafo
    // http://www.cplusplus.com/reference/cstdlib/calloc/
    //printf("tamanho estrutura %d",sizeof(TDigrafo*));
    D = (TDigrafo *) calloc(1, sizeof(TDigrafo) );
    
    // D = new TDigrafo( V )
    // atribui o numero de vertices para a estrtura
    D->V = V;
    // zero numero arcos
    D->A = 0;
    // aloca as entradas para a lista de adjacencia
    D->adj = (TNo ** )calloc(V,sizeof(TNo*));
    
    return D;
    
}
/*
 Função cria um arco v-w no digrafo.
 A função supõe que v e w são distintos, positivos e menores
 que V. Se o digrafo já tem arco v-w, a função não faz nada.
 Observação: reescrever para inserir ordenado os vertices adjacentes
 */
void insereA( TDigrafo *D, int v, int w){
    // pega o inicio da lista a partir da entrada
    // do vertice v
    TNo *aux = D->adj[v];
    TNo *ant=NULL;
    while( aux && aux->w <= w ){
        // verifica se já existe o arco v-w
        if( aux->w == w)
            return;
        ant = aux;
        aux = aux->prox;
    }
    // so para testar vou inserir w no inicio de adj[v]
    TNo *novo = (TNo*)calloc(1,sizeof(TNo));
    novo->w = w;
    novo->prox = aux;
    if( ant ) // se existe anterior
        // insere no final
        ant->prox = novo;
    else
        // insere no inicio
        D->adj[v] = novo;
    
    (D->A)++;
}
/*
 Função remove do digrafo o arco que tem ponta inicial v e
 ponta final w. A função supõe que v e w são distintos,
 positivos e menores que V. Se não existe arco v-w,
 método não faz nada.
 */
void removeA(TDigrafo *D, int v, int w){
    // verifica se existe o arco v-w
    /*if( D->adj[v][w]==1){
     D->adj[v][w] = 0;
     (D->A)--; // decrementa o numero de arcos
     }
     */
}
/*
 Para cada vértice v do digrafo, este método imprime,
 em uma linha, todos os vértices adjacentes a v.
 */
void show(TDigrafo *D){
    int v,w;
    
    for( v = 0; v < D->V; v++){ // vetor de listas
        printf("\n%d:",v);
        TNo *aux = D->adj[v];
        while( aux ){ // anda na lista
            printf(" %d",aux->w);
            aux = aux->prox;
        }
    }
}
/*
 Função desaloca a memória utilizado pelo dígrafo
 e pela matriz de adjacência.
 */
void libera(TDigrafo *D){
    
    int i;
    for(i=0;i<D->V;i++)
        free(D->adj[i]); // desloca linha
    
    // desaloca matriz
    free( D->adj );
    
    // desaloca digrafo
    //free( D );
    
}

/*
 Calcula grau de entrada
 */
int indeg(TDigrafo *D, int v){
    int i, grau = 0;
    
    for(i = 0; i < D->V; i++){ // vetor de listas
        TNo *aux = D->adj[i];
        while(aux){ // anda na lista
            if (aux->w == v) {
                grau++;
            }
            aux = aux->prox;
        }
    }
    
    return grau;
}

/*
 Calcula grau de saida
 */
int outdeg(TDigrafo *D, int v){
    int grau = 0;
    
    TNo *aux = D->adj[v];
    while(aux){ // anda na lista
        grau++;
        aux = aux->prox;
    }
    
    return grau;
}
