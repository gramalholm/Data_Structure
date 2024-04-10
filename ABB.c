#include<stdio.h>
#include<stdlib.h>

typedef struct Arvore{
    int info;
    struct Arvore *esq;
    struct Arvore *dir;
} Arvore;

//menu
int ImprimirOpcoes(){
    int num = 0;
    printf("\nSelecione sua opção:\n");
    printf("1.Ler Arvore \n");
    printf("2.Imprimir Arvore \n");
    printf("3.Verificar existencia de um elemento x \n");
    printf("4.Imprimir nivel de um no X \n");
    printf("5.Imprimir folhas menores que X \n");
    printf("6.Inserir No \n");
    printf("7.Remover No \n");
    printf("8.Sair\n");
    scanf(" %d", &num);
    return num;
}
//Opção 1.
Arvore* LerABB(FILE* fp){
    int num;
    char c;
    Arvore *av;
    
    fscanf(fp," %c", &c);
    fscanf(fp," %d", &num);

    if(num == -1){
        fscanf(fp," %c", &c);
        return NULL;
    }

    av =(Arvore*)malloc(sizeof(Arvore));
    av->info = num;
    av->esq = LerABB(fp);
    av->dir = LerABB(fp);
    fscanf(fp," %c", &c);
    if(av!=NULL){
        printf("\nArvore Lida Com Sucesso\n");
    }
    else
        printf("\nArvore Nula\n");
    return av;
}

//Opção 2.1
void PreOrdem(Arvore *a){
    if(a!=NULL){
        printf("%d ", a->info);
        PreOrdem(a->esq);
        PreOrdem(a->dir);
    }
}

//Opção 2.2.
void PosOrdem(Arvore* a){
    if(a!=NULL){
        PosOrdem(a->esq);
        PosOrdem(a->dir);
        printf("%d ", a->info);
    }
}

//Opção 2.3.
void EmOrdem(Arvore* a){
    if(a!=NULL){
        EmOrdem(a->esq);
        printf("%d ", a->info);
        EmOrdem(a->dir);
    }
}

//Opção 2.4(auxiliar)
void ImpNivel(Arvore *a,int cont, int n){
    if(a!=NULL){
        if(cont == n){
            printf("%d ", a->info);
        }
        ImpNivel(a->esq,cont+1,n);
        ImpNivel(a->dir,cont+1,n);
    }
}

//Opção 2.4(auxiliar)
int AlturaABB(Arvore *a){
    if(a == NULL)
        return 0;
    else{
        int he = AlturaABB(a->esq);
        int hd = AlturaABB(a->dir);
        if(he>hd)
            return he+1;
        else    
            return hd+1;
    }
}

//Opção 2.4.
void EmLargura(Arvore *a){
    if(a!=NULL){
        int  h = AlturaABB(a);
        int cont = 0;
        for(int i = 0; i < h; i++){
            ImpNivel(a, cont, i);
        }
    }
}


//Opção 2.
void imprimirABB(Arvore* a){
    if(a!=NULL){
        int i;
        printf("\nDigite a forma de impressão: \n1. Pre ordem\n2. Pos-ordem\n3. Em-ordem\n4. Em Largura\n");
        scanf(" %d", &i);
        if(i == 1){
            PreOrdem(a);
        }
        if(i == 2){
            PosOrdem(a);
        }
        if(i == 3){
            EmOrdem(a);
        }
        if(i == 4){
            EmLargura(a);
        }
    }
}

//Opção 3.
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

//Opção 4.
int imprimir_nivelX(Arvore *a, int cont, int x){
    if(a == NULL)
        return -1;
    else{
        if(a->info == x){
            return cont;
        }
        else if(x < a->info){
            return imprimir_nivelX(a->esq, cont + 1, x);
        }
        else{
            return imprimir_nivelX(a->dir, cont + 1, x);
        }

    }
}

//Opção 5.
void folha_mnr_q_x(Arvore *a, int x){
    if(a != NULL){
        if(x <= a->info){
            folha_mnr_q_x(a->esq, x);
        }
        else if(x > a->info){
            if(a->esq == NULL && a->dir == NULL)
                printf("%d ", a->info);
            else{
                folha_mnr_q_x(a->esq,x);
                folha_mnr_q_x(a->dir,x);
            }
        }
    }
}

//Opção 6.
Arvore *inserir(Arvore *a, int x){
    if(a == NULL){
        a = (Arvore*)malloc(sizeof(Arvore));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if(x <= a->info)
        a->esq = inserir(a->esq, x);
    else 
        a->dir = inserir(a->dir, x);
    return a;
}

//Opção 7.
Arvore *remover(Arvore *a, int x){
    if(a->info == x){
        if(a->esq == NULL && a->dir == NULL){
            free(a);
            return NULL;
        }
        else if(a->esq == NULL){
            Arvore *aux = a->dir;
            free(a);
            return aux;
        }
        else if(a->dir == NULL){
            Arvore *aux = a->esq;
            free(a);
            return aux;
        }
        else{
            Arvore *aux = a->esq;
            while(aux->dir != NULL){
                aux = aux->dir;
            }
            a->info = aux->info;
            a->esq = remover(a->esq, aux->info);
        }
    }
    else if(x < a->info)
        a->esq = remover(a->esq, x);
    else
        a->dir = remover(a->dir, x);
    return a;
}



//Opção 8
void RemoverABB(Arvore*a){
    if(a != NULL){
        RemoverABB(a->esq);
        RemoverABB(a->dir);
        free(a);
    }
}

int main(){
    int opcao;
    Arvore *a = NULL;
    while (opcao != 8){
        opcao = ImprimirOpcoes();
        if(opcao == 1){
            char caminho[100];
            printf("\nDigite o caminho do seu arquivo\n");
            fflush(stdin);
            scanf(" %99[^\n]", caminho);
            scanf("%*c");
            FILE *f = fopen(caminho, "rt");
            a = LerABB(f);
            fclose(f);

        }
        if(opcao == 2){
            imprimirABB(a);
        }
        if(opcao == 3){
            int n1, i;
            printf("Digite o elemento para verificar se existe na ABB\n");
            scanf(" %d", &n1);
            i = existeemABB(a, n1);
            if(i!=0)
                printf("O elemento %d Existe na ABB\n", n1);
            else
                printf("O elemento %d NAO Existe ena ABB\n", n1);
        }
        if(opcao == 4){
            int n2;
            int cont = 0;
            printf("Digite o nivel do elemento x \n");
            scanf(" %d", &n2);
            int i = imprimir_nivelX(a,cont,n2);
            if(i != -1)
                printf("Nivel de X = %d\n", i);  
            else{
                printf("Arvore Nula\n");
            }
        }
        if(opcao == 5){
            int n3;
            printf("Digite o numero para imprimir as folhas menores que ele: \n");
            fflush(stdin);
            scanf(" %d", &n3);
            folha_mnr_q_x(a,n3);
        }
        if(opcao == 6){
            int n4;
            printf("Digite o valor que voce quer inserir: \n");
            scanf(" %d", &n4);
            a = inserir(a,n4);
        }
        if(opcao == 7){
            int n5;
            printf("Digite o valor que voce quer remover: \n");
            scanf(" %d", &n5);
            a = remover(a,n5);
        }
        if(opcao == 8){
            RemoverABB(a);
            exit(0);
        }
    }
}
