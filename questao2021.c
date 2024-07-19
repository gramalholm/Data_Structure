#include<stdio.h>
#include<stdlib.h>

typedef struct Arvore{
    int info;
    struct Arvore *esq;
    struct Arvore *dir;
} Arvore;
//cont == 1 na main
int *ocorrencia(Arvore *a, int cont, int mc[2]){
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL){
            return mc;
        }else{
            if(a->esq->info == a->info){
                if(mc[1] >= cont){
                    mc[0] = a->info;
                    mc[1] = cont;
                    return ocorrencia(a->esq, cont+1, mc);
                }else{
                    return ocorrencia(a->esq, cont+1, mc);
                }
            }else{
                cont = 1;
                int ocEsq[2] = ocorrencia(a->esq, cont, mc);
                int ocDir[2] = ocorrencia(a->dir, cont, mc);
                if(ocEsq[1] >= ocDir[1]){
                    return ocEsq;
                }else{
                    return ocDir;
                }
            }
        }
    }
    return NULL;
}   