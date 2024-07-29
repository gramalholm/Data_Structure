#include<stdio.h>
#include<stdlib.h>
#include "fila.h"
#define N 100

struct fila{
    int vet[N];
    int tamanho;
    int primeiro;
};

Fila inicializar(){
    Fila f = (Fila)malloc(sizeof(struct fila));
    f->tamanho = 0;
    f->primeiro = 0; 
    return f;
}

int filaVazia(Fila f){
    if(f->tamanho <= 0){
        return 1;
    }
    return 0;
}

int inserir(Fila f, int x){
    if(f->tamanho >= N){
        return 0;
    }else{
        int pos = (f->primeiro + f->tamanho)%N;
        f->vet[pos] = x;
        f->tamanho++;
        return 1;
    }
}

int remover(Fila f, int *x){
    if(filaVazia(f)){
        return 0;
    }else{
        *x = f->vet[f->primeiro];
        f->primeiro = (f->primeiro+1)%N;
        f->tamanho--;
        return 1;
    }
}

void impFila(Fila f){
    for(int i = 0; i < f->tamanho; i++){
        int pos = (f->primeiro + i) % N;
        printf("%d ", f->vet[pos]);
    }
    printf("\n");
}

Fila destruir(Fila f){
    free(f);
    return NULL;
}