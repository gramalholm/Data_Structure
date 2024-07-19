#include<stdio.h>
#include<stdlib.h>

void imprimirCombinacoes(int *vet, int n, int pos){
    if(pos == 3){
        int contazero = 0;
        int contaum = 0;
        for(int i = 0; i<n; i++){
            if(vet[i] == 0){
                contazero++;
            }else{
                contaum++;
            }
            if(contazero > contaum ){
                printf("%d", vet[i]);
                printf("\n");
            }
        }
    }else{
        for(int i = 0; i<=1 ; i++){
            vet[pos] = i;
            imprimirCombinacoes(vet, n, pos+1);
        }
    }
}