#include<stdio.h>
#include<stdlib.h>

void somaVet(int *vet, int *vetN, int pos, int n){
    int soma = 0;
    if(pos == n){
        for(int i = 0; i<n; i++){
            soma += vet[i];
        }
        if(soma%2 == 0){
            for(int i = 0; i<n; i++){
                printf("%d ", vet[i]);
            }
            printf("\n");
        }
    }else{
        for(int i = 0; i<=3; i++){
            vet[pos] = vetN[i];
            somaVet(vet, vetN, pos+1, n);
        }
    }
}

int main(){
    int vet[4];
    int vetN[] = {15,31,55,44};
    somaVet(vet, vetN, 0, 4);
}