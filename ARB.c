#include<stdio.h>
#include<stdlib.h>

typedef struct ArvRubroNegra{
    int info;
    char cor;
    struct ArvRubroNegra *esq;
    struct ArvRubroNegra *dir;
}ArvRubroNegra;

ArvRubroNegra *lerARB(FILE* f){
    int num;
    char c;
    char cor;

    fscanf(f,"%c", &c);
    fscanf(f,"%d", &num);
    fscanf(f,"%c", &cor);

    if(num == -1){
        fscanf(f,"%c",&c);
        return NULL;
    } 

    ArvRubroNegra *a = (ArvRubroNegra*)malloc(sizeof(ArvRubroNegra));
    if(a == NULL){
        printf("Impossivel ler Arvore\n");
        exit(EXIT_FAILURE);
    }
    printf("\nArvore lida com sucesso\n");
    a->info = num;
    a->cor = cor;
    a->esq = lerARB(f);
    a->dir = lerARB(f);
    fscanf(f,"%c", &c);
    return a;

}

int ExisteARB(ArvRubroNegra *a, int x){
    if(a!=NULL){
        if(a->info == x)
            return 1;
        else if(a->info > x)
            return ExisteARB(a->esq, x);
        else
            return ExisteARB(a->dir, x);
    }
    return 0;
}

int H_negra(ArvRubroNegra *a, int *hN){
    if(a!=NULL){
        if(a->cor == 'p'){
            *hN+1;
            return H_negra(a->esq, hN);
        }
        else    
            return H_negra(a->esq, hN);
    }
    return 0;
}