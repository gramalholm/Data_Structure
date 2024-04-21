#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int totalElem = 0;

int menu(){
    int op = 0;
    printf("\nDigite a opcao desejada\n");
    printf("1.Inserir elemento no Heap\n");
    printf("2.Remover elemento do Heap\n");
    printf("3.Imprimir Heap\n");
    printf("4.Sair\n");
    scanf("%d", &op);
    return op;
}

int indicePai(int x){
    int indice = floor((x-1)/2);
    if(x<=0 || x >= totalElem)
        return -1;
    else
        return indice;
}

int indiceFEsq(int x){
    int indice = (2*x)+ 1;
    if(x>=totalElem || indice>=totalElem)
        return -1;
    else
        return indice;
}
int indiceFDir(int x){
    int indice = (2*x) + 2;
    if(x>=totalElem || indice>=totalElem)
        return -1;
    else
        return indice;
}

void ajustaSubindo(int n, int *heap){
    if(n != -1){
        int pai = indicePai(n);
        if(pai != -1){
            if(heap[n] < heap[pai]){
                int aux = heap[n];
                heap[n] = heap[pai];
                heap[pai] = aux;
                ajustaSubindo(pai,heap);
            }
        }
    }
}

void ajustDescendo(int n, int *heap){
    if(n!=-1 && indiceFEsq(n) != -1)
    {
        int indicemenor = indiceFEsq(n);
        if(indiceFDir(n)!=-1 && heap[indiceFDir(n)] < heap[indiceFEsq(n)])
            indicemenor = indiceFDir(n);
        if(heap[indicemenor] < heap[n]){
            int aux = heap[n];
            heap[n] = heap[indicemenor];
            heap[indicemenor] = aux;
            ajustDescendo(indicemenor,heap);
        }
    }
}

void inserir(int n, int heap[n], int x){
    if(n > totalElem){
        heap[totalElem] = x;
        totalElem ++;
        ajustaSubindo(totalElem - 1, heap);
    }
    else
        printf("Numero de elementos ultrapassou o maximo definido\n");
}

int remover(int *heap){
    if(totalElem == 0)
        return -1;
    else{
        int retorno = heap[0];
        heap[0] = heap[totalElem - 1];
        totalElem--;
        ajustDescendo(0,heap);
        return retorno;
    }
}

void imprimir(int *heap,int i){
    if(heap != NULL){
        if(i < totalElem){
            printf("%d ", heap[i]);
            imprimir(heap,2*i + 1);
            imprimir(heap,2*i + 2);
        }
    }
    else    
        printf("Heap vazia\n");
}

int main(){
    int n;
    int *heap;
    printf("Digite o tamanho do heap: \n");
    scanf("%d", &n);
    heap = malloc(n*sizeof(int));
    int op = 0;
    while(op != 4){ 
        op = menu();
        if(op == 1){
            int i;
            printf("Digite o Numero que deseja inserir: \n");
            scanf(" %d", &i);
            inserir(n,heap,i);
        }
        if(op == 2){
            int elemremovido = remover(heap);
            if(elemremovido != -1)
                printf("Elemento %d removido\n", elemremovido);
            else    
                printf("Heap vazia\n");
        
        }
        if(op == 3){
            int i = 0;
            imprimir(heap, i);
        }
        if(op == 4){
            free(heap);
            exit(0);
        }
    }
}
