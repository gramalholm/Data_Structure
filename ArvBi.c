
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
} arvore; 

//escopo das funções usadas
int Imprimir_opcoes();
arvore *Ler_Arvore(FILE *fp);
void Imprimir_arvore(arvore *a);
void Pre_ordem(arvore *a);
void Pos_ordem(arvore *a);
void Em_ordem(arvore *a);
int Arvore_balanceada(arvore *a);
void Imprimir_Nivel(arvore *a, int cont, int n);
int Altura(arvore *a);
int Existe_elem(arvore *a, int x);
char *Arquivo(char *diretorio, arvore **arv);
int Num_elem(arvore *a);
void Imp_folhas(arvore *a);
void Arvore_cheia(arvore *a);
void Imprimir_Nivel_De_X(arvore *a,int cont, int x);
void Liberar_arvore(arvore *a);
int no_interno(arvore *a);
void imp_filhos(arvore *a, int x);
void imp_pai(arvore *a, int x);
int esta_ordenada(arvore *a);

int main(){
    int opcao;
    arvore *a = NULL;
    while (opcao != 13){
        opcao = Imprimir_opcoes();
        if(opcao == 1){
            char caminho_arq[100];
            printf("\nDigite o caminho do seu arquivo\n");
            fflush(stdin);
            scanf(" %99[^\n]", caminho_arq);
            scanf("%*c");
            printf(" %s", Arquivo(caminho_arq, &a));
        }
        if(opcao == 2){
            Imprimir_arvore(a);
        }
        if(opcao == 3){
            int n, aux;
            scanf("%d", &aux);
            n = Existe_elem(a,aux);
            if(n == 1)
                printf("\nExiste\n");
            else    
                printf("\nN existe\n");
        }
        if(opcao == 4){
            printf("\nNumero de elementos: %d elementos na arvore\n", Num_elem(a));
        }
        if(opcao == 5){
            Imp_folhas(a);
        }
        if(opcao == 6){
            int aux =Arvore_balanceada(a);
            if(aux == 0)
                printf("\nArvore Nao Balanceada\n");
            else
                printf("\nArvore Balanceada\n");
        }
        if(opcao == 7){
            Arvore_cheia(a);
        }
        if(opcao == 8){
            int cont = 0;
            int aux = 0;
            printf("\nDigite o elemento: \n");
            scanf(" %d", &aux);
            Imprimir_Nivel_De_X(a,cont,aux);
        }
        if(opcao == 9){
            int n = no_interno(a);
            printf("\nNumeros de nos intenros : %d\n", n);
        }
        if(opcao == 10){
            int x = 0;
            scanf(" %d", &x);
            imp_filhos(a,x);
        }
        if(opcao == 11){
            int x = 0;
            scanf(" %d", &x);
            imp_pai(a,x);

        }
        if(opcao == 12){
            int i = esta_ordenada(a);
            if(i == 1)
                printf("\nOrdenada\n");
            if(i == 0)
                printf("\nN ordenada\n");
        }
        if(opcao == 13){
            Liberar_arvore(a);
            exit(0);
        }
    }
}  

//auxiliar.
int Imprimir_opcoes()
{
    int num = 0;
    printf("\n1.Ler Arvore \n");
    printf("2.Imprimir Arvore \n");
    printf("3.Verificar existencia de um elemento x \n");
    printf("4.Contar numero de elementos \n");
    printf("5.Imprimir folhas da Arvore \n");
    printf("6.Verificar se Arvore esta balanceada \n");
    printf("7.Verificar se Arvore esta cheia \n");
    printf("8.Imprimir nivel de um no X \n");
    printf("9.Imprime os nos internos \n");
    printf("10.Imprime os Nos filhos de X \n");
    printf("11.Imprime o No pai de X\n");
    printf("12.Verificar se a arvore é Ordenada\n");
    printf("13.Sair\n");
    scanf(" %d", &num);
    return num;
}

//opção 1.
arvore *Ler_Arvore(FILE *fp){
    char c;
    int num;
    arvore *av; 
    fscanf(fp," %c", &c);
    fscanf(fp," %d", &num);

    if(num == -1){
        fscanf(fp," %c", &c);
        return NULL;
    }

    av = (arvore*)malloc(sizeof(arvore));
    av->info = num;
    av->esq=Ler_Arvore(fp);
    av->dir=Ler_Arvore(fp);
    fscanf(fp," %c", &c);
    return av;
}

//auxiliar para abrir o arquivo
char *Arquivo(char *diretorio, arvore **arv){
    FILE* f;
    f = fopen(diretorio, "rt");

    if(f == NULL){
        return "\nNao foi possivel abrir esse arquivo\n";
    }
    *arv = Ler_Arvore(f);
    fclose(f);
    return "\nUma Arvore foi criada\n";
}

//opção 2.
void Imprimir_arvore(arvore *a){
    if(a != NULL){
        int i;
        int h;
        printf("\n opcoes: \n1. Pre-ordem \n 2. Pos-ordem \n 3. Em-ordem \n 4. Em largura \n Digite a Opcao: \n");
        scanf("%d", &i);
            if(i == 1)
                Pre_ordem(a);
            if(i == 2)
                Pos_ordem(a);
            if(i == 3)
                Em_ordem(a); 
            if(i == 4){
                h = Altura(a); 
                int cont = 0;
                for(int i = 0; i<h; i++){
                    Imprimir_Nivel(a,cont,i);
                }
            }
    }
}

//auxiliar opção 2(1).
void Pre_ordem(arvore *a){
    if(a != NULL){
        printf("%d ", a->info);
        Pre_ordem(a->esq);
        Pre_ordem(a->dir);
    }
}
//auxiliar opção 2(2).

void Pos_ordem(arvore *a){
    if(a != NULL){
        Pos_ordem(a->esq);
        Pos_ordem(a->dir);
        printf("%d ", a->info);
    }
}

//auxiliar opção 2(3).
void Em_ordem(arvore *a){
    if(a != NULL){
        Em_ordem(a->esq);
        printf("%d ", a->info);
        Em_ordem(a->dir);
    }
}

//auxiliar opção 2(4).
void Imprimir_Nivel(arvore *a, int cont, int n){
    if(a!=NULL){
        if(cont == n){
            printf("%d ", a->info);
        }
        Imprimir_Nivel(a->esq,cont+1,n);
        Imprimir_Nivel(a->dir,cont+1,n);
    }
}

//auxiliar para achar altura
int Altura(arvore *a){
    if(a == NULL)
        return 0;
    else{
        int he = Altura(a->esq);
        int hd = Altura(a->dir);
        if(he>hd)
            return he+1;
        else    
            return hd+1;
    }
}

//opção 3.
int Existe_elem(arvore *a, int x){
    if(a != NULL){
        if(a->info == x)
            return 1;
        else{
            return Existe_elem(a->esq,x) || Existe_elem(a->dir,x);
        }
    }
    return 0;
}

//opção 4.
int Num_elem(arvore *a){
    if(a == NULL)
        return 0;
    else{
        return 1 + Num_elem(a->esq) + Num_elem(a->dir);
    }
}

//opção 5.
void Imp_folhas(arvore *a){
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL)
            printf("\n%d\n", a->info);
        Imp_folhas(a->esq);
        Imp_folhas(a->dir);
    }
}

//opção 6.
int Arvore_balanceada(arvore *a){
    if(a!=NULL){
        int he = Altura(a->esq);
        int hd = Altura(a->dir);
        if(abs(he - hd) > 1)
            return 0;
        else{
            int b1 = Arvore_balanceada(a->esq);
            int b2 = Arvore_balanceada(a->dir);
            if(b1 == 0 || b2 == 0)
                return 0;
            return 1;
        }
    }
    return 1;
}

//opção 7.
void Arvore_cheia(arvore *a){
    int h = Altura(a);
    int total = pow(2,h) - 1;
    if(a!=NULL){
        if(Num_elem(a) == total)
            printf("\nA Arvore esta cheia\n");
        printf("\nA Arvore Nao esta cheia\n");
    }
}

//opção 8.
void Imprimir_Nivel_De_X(arvore *a,int cont, int x){
    if(a!=NULL){
        if(a->info == x)
            printf("\nNivel do elemento %d = %d\n", x, cont);
        else{
            Imprimir_Nivel_De_X(a->esq, cont + 1, x);
            Imprimir_Nivel_De_X(a->dir, cont + 1, x);
        }
    }
}
//opção 9.
void Liberar_arvore(arvore *a){
    if(a != NULL){
        Liberar_arvore(a->esq);
        Liberar_arvore(a->dir);
        free(a);
    } 
} 

int no_interno(arvore *a){
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL)
            return 0;
        else{
            int n_int = 1 + no_interno(a->esq) + no_interno(a->dir);
            return n_int;
        }  
    }
    return 0;
}

void imp_filhos(arvore *a, int x) {
    if (a != NULL) {
        if (a->info == x){
            if (a->esq != NULL) {
                printf(" %d", a->esq->info);
            }
            if (a->dir != NULL) {
                printf(" %d", a->dir->info);
            }
        } 
        else{
            imp_filhos(a->esq, x);
            imp_filhos(a->dir, x);
        }
    }
}

void imp_pai(arvore *a, int x){
    if(a!=NULL){
        if ((a->esq != NULL && a->esq->info == x) || (a->dir != NULL && a->dir->info == x)){
            printf("%d \n", a->info);
        }
        else{
            imp_pai(a->esq, x);
            imp_pai(a->dir, x);
        }
    }
}

int esta_ordenada(arvore *a){
    if(a != NULL){  
        if(a->esq != NULL){
            if(a->esq->info > a->info)
                return 0;
        }
        if(a->dir != NULL){
            if(a->dir->info <= a->info)
                return 0;
        }
        return esta_ordenada(a->esq) * esta_ordenada(a->dir);
    }
    return 1;
}