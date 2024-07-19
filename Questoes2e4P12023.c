#include<stdio.h>
#include<stdlib.h>

int verificaHN(Arb* a){
    if(a == NULL){
        return 0;
    }else{
        int hne = verificaHN(a->esq);
        int hnd = verificaHN(a->dir);
        if(hne == hnd){
            if(a->cor == 'p'){
                hne = 1;
                return hne;
            }
            else{
                return hne;
            }
        }else{
            return 0;
        }
    }
}

int existeemABB(Arvore *a, int x){
    if(a!=NULL){
        if(a->info == x)
            return 1;
        else{
            if(x < a->info)
                return existeemABB(a->esq, x);
            else if(x > a->info)
                return existeemABB(a->dir, x);
        }
    }
    return 0;
}

void existeEmDuasArvores(Arvore *a, Arvore *b){
    if(a != NULL){
        if(existeemABB(b, a->info)){
            printf("%d", a->info);
            existeEmDuasArvores(a->esq, b);
            existeEmDuasArvores(a->dir,b);
        }
        else{
            printf("%d nao existe na arvore b", a->info);
            existeEmDuasArvores(a->esq, b);
            existeEmDuasArvores(a->dir, b);
        }
    }
}