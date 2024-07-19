#include<stdio.h>
#include<stdlib.h>

typedef struct lista{
    int destino;
    int custo;
    struct lista *prox;
} lista;

int menu(){
    int opcao = 0;
    printf("\n----- MENU -----\n");
    printf("1. inserir aresta\n");
    printf("2. remover aresta\n");
    printf("3. imprimir grafo\n");
    printf("4. imprimir graus de entrada e saida\n");
    printf("5. verificar se o grafo e completo\n");
    printf("9. sair\n");
    scanf(" %d", &opcao);
    return opcao;
}

void inicializa_grafo(lista **grafo, int n){
    for(int i = 0; i<=n; i++){
        grafo[i] = NULL;
    }
}

lista *inserirLista(lista *l, int destino, int custo){
    lista *laux = (lista*)malloc(sizeof(lista));
    laux->destino = destino;
    laux->custo = custo;
    laux->prox = l;
    return laux;
}

int existenaLista(lista *l, int x){
    lista *aux = l;
    while(aux != NULL){
        if(aux->destino == x){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void inserirAresta( lista **grafo, int origem, int dest, int custo, int n){
    if(origem > n){
        printf("Origem incompativel com o Grafo");
    }else if(existenaLista(grafo[origem], dest)){
        printf("Elemento de origem = %d e destino = %d já existe no grafo", origem, dest);
    }else{
        grafo[origem] = inserirLista(grafo[origem], dest, custo);
    }
}

lista *removerLista(lista* l, int destino){
    if(l != NULL){
        if(l->destino == destino){
            lista* laux = l->prox;
            free(l);
            return laux;
        }else{
            l->prox = removerLista(l, destino);
        }
    }
    return l;
}

void removerAresta(lista **grafo,int origem, int destino){
    grafo[origem] = removerLista(grafo[origem], destino);
}

void imprimirLista(lista *l){
    if(l != NULL){
        printf("-->(destino: %d | custo: %d)", l->destino, l->custo);
        imprimirLista(l->prox);
    }else{
        printf("-->NULL\n");
    }
}

void imprimirGrafo(lista **g, int n){
    for(int i = 1; i <= n; i++){
        printf("\n\t%d", i);
        imprimirLista(g[i]);
    }
}

int contaGrauEntrada(lista **g, int x, int n){
    int cont = 0;
    for(int i = 1; i<=n; i++){
        while(g[i] != NULL){
            if(g[i]->destino == x){
                cont ++;
            }
            g[i] = g[i]->prox;
        }
    }
    return cont;
}

int tamanhoLista(lista *l){
    lista* aux = l;
    int cont = 0;
    while(aux!=NULL){
        cont++; 
        aux = aux->prox;      
    }
    return cont;
}


void imprimeGraus(lista **g,int pos, int n){
    int grauentrada = contaGrauEntrada(g, pos, n);
    int grausaida = tamanhoLista(g[pos]);
    printf("Grau de entrada = %d e Grau de saida = %d", grauentrada, grausaida);

}

int grafoCompleto(lista **g, int pos, int n){
    int total = n-1;
    int cont = tamanhoLista(g[pos]);
    if(cont == total){
        return 1;
    }else{
        return 0;
    }

}

void freeLista(lista *l){
    if(l!=NULL){
        freeLista(l->prox);
        free(l);
    }
}

void freeGrafo(lista **g, int n){
    for(int i = 1; i<=n; i++){
        freeLista(g[i]);
    }
    free(g);
}

int existe(int *vet, int dado, int n){
    for(int i = 0; i<n; i++){
        if(dado == vet[i]){
            return 1;
        }else{
            return 0;
        }
    }
}

void impCaminhos(lista **g, int *vet, int dest, int pos){
    if(vet[pos-1] == dest){
        for(int i = 0; i<=pos; i++){
            printf("%d ", vet[i]);
        }
        printf("\n");
    }
    else{
        lista *laux = g[vet[pos-1]];
        while(laux != NULL){
            if(!existe(vet,laux->destino, pos)){
                vet[pos] = laux->destino;
                impCaminhos(g,vet,dest,pos+1);
            }
            laux = laux->prox;
        }
    }
}

void caminhoMaisCurto(lista **g, int *vet, int dest, int pos){
    if(vet[pos-1] == dest){
        
        for(int i = 0; i<=pos; i++){
            printf("%d ", vet[i]);
        }
        printf("\n");
    }
    else{
        lista *laux = g[vet[pos-1]];
        while(laux != NULL){
            if(!existe(vet,laux->destino, pos)){
                vet[pos] = laux->destino;
                impCaminhos(g,vet,dest,pos+1);
            }
            laux = laux->prox;
        }
    }
}

int main(){
    int n;
    printf("Digite o tamano do grafo: \n");
    scanf("%d", &n);
    lista **g; 
    g = (lista**)malloc((n+1)*sizeof(lista*));
    inicializa_grafo(g, n);
    int opcao = 0;
    while(opcao != 9){
        opcao = menu();
        if(opcao == 1){
            int destino1; 
            int custo1;
            int origem1;
            printf("Digite a origem da aresta que deseja inserir\n");
            scanf(" %d", &origem1);
            while(1){
                printf("Digite o destino da aresta que deseja inserir\n");
                scanf(" %d", &destino1);
                if(destino1 == origem1 || destino1 > n){
                    printf("Destino incompativel com o Grafo, tente novamente\n");
                }else{
                    break;
                }
            }
            printf("Digite o custo da aresta que deseja inserir\n");
            scanf(" %d", &custo1);
            inserirAresta(g,origem1, destino1, custo1, n);
        }
        if(opcao == 2){
            int dest;
            int origem;
            printf("Digite a origem da aresta que deseja remover\n");
            scanf(" %d", &origem);
            printf("Digite o destino da aresta que deseja remover\n");
            scanf(" %d", &dest);
            removerAresta(g,origem, dest);
        }
        if(opcao == 3){
            imprimirGrafo(g,n);
        }
        if(opcao == 4){
            int origem;
            printf("Digite a origem que deseja imprimir os graus\n");
            scanf(" %d", &origem);
            imprimeGraus(g,origem,n);
        }
        if(opcao == 5){
            int pos = 1;
            int n = grafoCompleto(g,pos, n);
            if(n == 1){
                printf("Este Grafo esta completo\n");
            }else{
                printf("Este Grafo nao esta completo\n");
            }
        }
        if(opcao == 6){
            int origem, destino;
            int pos = 1;
            int vet[n];
            printf("Digite a origem e o destino para calcular o caminho\n");
            scanf("%d %d", &origem, &destino);
            vet[0] = origem;

        }
        if(opcao == 7){

        }
        if(opcao == 8){

        }
        if(opcao == 9){
            freeGrafo(g, n);
        }
    }

}