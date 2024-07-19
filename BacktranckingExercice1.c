#include<stdio.h>
#include<stdlib.h>

void combinacaoAEI(char *vet, int pos, int n, char *vetaux){
    if(pos == 3){
        int contaA = 0;
        int contaE = 0;
        int contaI = 0;
        for(int i = 0; i<n ; i++){
            if(vet[i] == 'a'){
                contaA++;
            }else if(vet[i] == 'e'){
                contaE++;
            }else{
                contaI++;
            }
        }
        if(contaA > (contaE + contaI)){
            for(int i = 0; i<n;i++){
                printf("%c", vet[i]);
            }
            printf("\n");
        }
    }else{
        for(int i = 0; i<=2; i++){
            vet[pos] = vetaux[i];
            combinacaoAEI(vet, pos+1, n, vetaux);
        }
    }
}

int main(){
    char vetaux[] = {'a','e','i'};
    char vet[3];
    int pos = 0;
    int n = 3;
    combinacaoAEI(vet, pos, n, vetaux);
}