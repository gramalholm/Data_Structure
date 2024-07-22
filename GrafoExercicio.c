#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int destino;
    int custo;
    struct lista *prox;
} lista;

int menu() {
    int opcao = 0;
    printf("\n----- MENU -----\n");
    printf("1. Inserir aresta\n");
    printf("2. Remover aresta\n");
    printf("3. Imprimir grafo\n");
    printf("4. Imprimir graus de entrada e saída\n");
    printf("5. Verificar se o grafo é completo\n");
    printf("6. Imprimir todos os caminhos da origem até um destino\n");
    printf("7. Imprimir o menor caminho de uma origem até um destino\n");
    printf("8. Imprimir o caminho de menor custo de uma origem até um destino\n");
    printf("9. Sair\n");
    scanf("%d", &opcao);
    return opcao;
}

void inicializa_grafo(lista **grafo, int n) {
    for (int i = 0; i <= n; i++) {
        grafo[i] = NULL;
    }
}

lista *inserirLista(lista *l, int destino, int custo) {
    lista *laux = (lista *)malloc(sizeof(lista));
    laux->destino = destino;
    laux->custo = custo;
    laux->prox = l;
    return laux;
}

int existenaLista(lista *l, int x) {
    lista *aux = l;
    while (aux != NULL) {
        if (aux->destino == x) {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void inserirAresta(lista **grafo, int origem, int dest, int custo, int n) {
    if (origem > n) {
        printf("Origem incompatível com o Grafo\n");
    } else if (existenaLista(grafo[origem], dest)) {
        printf("Elemento de origem = %d e destino = %d já existe no grafo\n", origem, dest);
    } else {
        grafo[origem] = inserirLista(grafo[origem], dest, custo);
    }
}

lista *removerLista(lista *l, int destino) {
    if (l != NULL) {
        if (l->destino == destino) {
            lista *laux = l->prox;
            free(l);
            return laux;
        } else {
            l->prox = removerLista(l->prox, destino);
        }
    }
    return l;
}

void removerAresta(lista **grafo, int origem, int destino) {
    grafo[origem] = removerLista(grafo[origem], destino);
}

void imprimirLista(lista *l) {
    if (l != NULL) {
        printf("-->(destino: %d | custo: %d)", l->destino, l->custo);
        imprimirLista(l->prox);
    } else {
        printf("-->NULL\n");
    }
}

void imprimirGrafo(lista **g, int n) {
    for (int i = 1; i <= n; i++) {
        printf("\n\t%d", i);
        imprimirLista(g[i]);
    }
}

int contaGrauEntrada(lista **g, int x, int n) {
    int cont = 0;
    for (int i = 1; i <= n; i++) {
        lista *aux = g[i];
        while (aux != NULL) {
            if (aux->destino == x) {
                cont++;
            }
            aux = aux->prox;
        }
    }
    return cont;
}

int tamanhoLista(lista *l) {
    lista *aux = l;
    int cont = 0;
    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

void imprimeGraus(lista **g, int pos, int n) {
    int grauentrada = contaGrauEntrada(g, pos, n);
    int grausaida = tamanhoLista(g[pos]);
    printf("Grau de entrada = %d e Grau de saida = %d\n", grauentrada, grausaida);
}

int grafoCompleto(lista **g, int n) {
    for (int i = 1; i <= n; i++) {
        if (tamanhoLista(g[i]) != n - 1) {
            return 0;
        }
    }
    return 1;
}

void freeLista(lista *l) {
    if (l != NULL) {
        freeLista(l->prox);
        free(l);
    }
}

void freeGrafo(lista **g, int n) {
    for (int i = 1; i <= n; i++) {
        freeLista(g[i]);
    }
    free(g);
}

int existe(int *vet, int dado, int n) {
    for (int i = 0; i < n; i++) {
        if (dado == vet[i]) {
            return 1;
        }
    }
    return 0;
}

void impCaminhos(lista **g, int *vet, int dest, int pos) {
    if (vet[pos - 1] == dest) {
        printf("\n");
        for (int i = 0; i < pos; i++) {
            printf("%d ", vet[i]);
        }
        printf("\n");
    } else {
        lista *laux = g[vet[pos - 1]];
        while (laux != NULL) {
            if (!existe(vet, laux->destino, pos)) {
                vet[pos] = laux->destino;
                impCaminhos(g, vet, dest, pos + 1);
            }
            laux = laux->prox;
        }
    }
}

void caminhoMaisCurto(lista **g, int *vet, int dest, int pos, int *menorCaminho, int *vetorMenor) {
    if (vet[pos - 1] == dest) {
        if (pos < *menorCaminho) {
            *menorCaminho = pos;
            for (int i = 0; i < pos; i++) {
                vetorMenor[i] = vet[i];
            }
        }
    } else {
        lista *laux = g[vet[pos - 1]];
        while (laux != NULL) {
            if (!existe(vet, laux->destino, pos)) {
                vet[pos] = laux->destino;
                caminhoMaisCurto(g, vet, dest, pos + 1, menorCaminho, vetorMenor);
            }
            laux = laux->prox;
        }
    }
}

int custoAresta(lista **g, int a, int b) {
    lista *l = g[a];
    while (l != NULL) {
        if (l->destino == b) {
            return l->custo;
        }
        l = l->prox;
    }
    return -1;
}

int calcularCusto(lista **g, int *vet, int n) {
    int custo = 0;
    for (int i = 1; i < n; i++) {
        custo += custoAresta(g, vet[i - 1], vet[i]);
    }
    return custo;
}

void menosCusto(lista **g, int *vet, int dest, int pos, int *menorCusto, int *vetorMenorCusto, int *tam) {
    if (vet[pos - 1] == dest) {
        int custo = calcularCusto(g, vet, pos);
        if (custo < *menorCusto) {
            *menorCusto = custo;
            *tam = pos;
            for (int i = 0; i < pos; i++) {
                vetorMenorCusto[i] = vet[i];
            }
        }
    } else {
        lista *laux = g[vet[pos - 1]];
        while (laux != NULL) {
            if (!existe(vet, laux->destino, pos)) {
                vet[pos] = laux->destino;
                menosCusto(g, vet, dest, pos + 1, menorCusto, vetorMenorCusto, tam);
            }
            laux = laux->prox;
        }
    }
}

int main() {
    int n;
    printf("Digite o tamanho do grafo: \n");
    scanf("%d", &n);
    lista **g = (lista **)malloc((n + 1) * sizeof(lista *));
    inicializa_grafo(g, n);
    int opcao = 0;
    while(opcao != 9) {
        opcao = menu();
        if(opcao == 1){
            int origem1, destino1, custo1;
            printf("Digite a origem da aresta que deseja inserir\n");
            scanf("%d", &origem1);
            while (1) {
                printf("Digite o destino da aresta que deseja inserir\n");
                scanf("%d", &destino1);
                if (destino1 == origem1 || destino1 > n) {
                    printf("Destino incompatível com o Grafo, tente novamente\n");
                } else {
                    break;
                }
            }
            printf("Digite o custo da aresta que deseja inserir\n");
            scanf("%d", &custo1);
            inserirAresta(g, origem1, destino1, custo1, n);
        }
        if(opcao == 2){
            int origem, destino;
            printf("Digite a origem da aresta que deseja remover\n");
            scanf("%d", &origem);
            printf("Digite o destino da aresta que deseja remover\n");
            scanf("%d", &destino);
            removerAresta(g, origem, destino);
        }
        if(opcao == 3){
            imprimirGrafo(g, n);
        }
        if(opcao == 4){
            int origem;
            printf("Digite a origem que deseja imprimir os graus\n");
            scanf("%d", &origem);
            imprimeGraus(g, origem, n);
        }
        if(opcao == 5){
            if(grafoCompleto(g, n)) {
                printf("Este Grafo esta completo\n");
            }else{
                printf("Este Grafo nao esta completo\n");
            }
        }
        if(opcao == 6){
            int origem, destino;
            printf("Digite a origem\n");
            scanf("%d", &origem);
            printf("Digite o destino\n");
            scanf("%d", &destino);
            int *vet = (int*)malloc(n*sizeof(int));
            vet[0] = origem;
            impCaminhos(g, vet, destino, 1);
            free(vet);
        }
        if(opcao == 7){
            int origem, dest;
            int menorCaminho = n + 1;
            int *vetorMenor = (int*)malloc(n*sizeof(int));
            printf("Digite a origem\n");
            scanf("%d", &origem);
            printf("Digite o destino\n");
            scanf("%d", &dest);
            int *vet = (int*)malloc(n*sizeof(int));
            vet[0] = origem;
            caminhoMaisCurto(g, vet, dest, 1, &menorCaminho, vetorMenor);
            printf("Menor caminho: ");
            for (int i = 0; i < menorCaminho; i++) {
                printf("%d ", vetorMenor[i]);
            }
            printf("\n");
            free(vet);
            free(vetorMenor);
        }
        if(opcao == 8){
            int origem, dest;
            int menorCusto = 99999999;
            int tamanho = 0;
            int *vetorMenorCusto = (int*)malloc(n*sizeof(int));
            printf("Digite a origem\n");
            scanf("%d", &origem);
            printf("Digite o destino\n");
            scanf("%d", &dest);
            int *vet = (int*)malloc(n*sizeof(int));
            vet[0] = origem;
            menosCusto(g, vet, dest, 1, &menorCusto, vetorMenorCusto, &tamanho);
            printf("Caminho de menor custo: ");
            for (int i = 0; i < tamanho; i++) {
                printf("%d ", vetorMenorCusto[i]);
            }
            printf("\n");
            free(vet);
            free(vetorMenorCusto);
        }
        if(opcao == 9){
            freeGrafo(g, n);
        }
    }
}