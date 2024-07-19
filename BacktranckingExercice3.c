#include<stdio.h>
#include<stdlib.h>

void impMoedas(int *vet, int *moedas, int pos, int n,int valor){
    if(pos == n){
        int soma = 0;
        for(int i = 0; i<n;i++){
            soma += vet[i]*moedas[i];
        }
        if(soma == valor){
            for(int i = 0; i<n; i++){
                printf("%d moedas de %d centavos ", vet[i], moedas[i]);
            }
            printf(" ou\n");
        }
    }else{
        for(int i = 0; i<=valor; i++){
            vet[pos] = i;
            impMoedas(vet,moedas,pos+1,n,valor);
        }
    }
}

int main(){
    int moedas[] = {50,25,10,5,1};
    int vet[] = {0, 0, 0, 0, 0};
    int valor;
    printf("Digite o valor:\n");
    scanf("%d", &valor);
    impMoedas(vet, moedas, 0, 5, valor);
}