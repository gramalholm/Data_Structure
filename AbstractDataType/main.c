#include<stdio.h>
#include "fila.h"

int menu(){
    int opcao = 0;
    printf("\n------ Menu ------   \n");
    printf("1. Inserir elemento\n");
    printf("2. Remover elemento\n");
    printf("3. Imprimir fila\n");
    printf("4. Sair \n");
    scanf("%d", &opcao);
    return opcao;
}

int main(){
    int op = 0;
    Fila f = inicializar();
    while(op!=4){
        op = menu();
        if(op == 1){
            int elemento, verificador;
            printf("Digite o elemento que deseja inserir\n");
            scanf("%d", &elemento);
            verificador = inserir(f, elemento);
            if(verificador == 1){
                printf("Elemento inserido com sucesso\n");
            }else{
                printf("Fila Cheia\n");
            }
        }
        if(op == 2){
            int elemremovido,verificador;
            verificador = remover(f, &elemremovido);
            if(verificador == 1){
                printf("Elemento %d removido do inicio da fila\n", elemremovido);
            }else{
                printf("Fila Vazia\n");
            }
        }
        if(op == 3){
            impFila(f);
        }
        if(op == 4){
            destruir(f);
            printf("Fila destruida!\n");
        }
    }
}