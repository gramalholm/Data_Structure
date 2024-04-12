#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//tive que alterar algumas funções comparado ao outro trab pois estava dando problema com o buffer
//Aluno: Gabriel Ramalho Lima
//Matricula: 12306006

typedef struct AVL{
    int info;
    int FB;
    struct AVL *esq;
    struct AVL *dir;
}AVL;

int ImprimirOpcoes(){
    int num = 0;
    printf("\nSelecione sua opcao:\n");
    printf("1.Ler AVL \n");
    printf("2.Imprimir AVL \n");
    printf("3.Verificar existencia de um elemento x \n");
    printf("4.Imprimir nivel de um no X \n");
    printf("5.Imprimir folhas menores que X \n");
    printf("6.Inserir No \n");
    printf("7.Remover No \n");
    printf("8.Sair\n");
    scanf(" %d", &num);
    return num;
}

AVL* LerArvoreAVL(FILE* fp){
    int num;
    char c;
    fscanf(fp," %c", &c);
    fscanf(fp," %d", &num);

    if(num == -1){
        fscanf(fp," %c", &c);
        return NULL;
    }

    AVL *av =(AVL*)malloc(sizeof(AVL));
    if (av == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(EXIT_FAILURE);
    }
    av->info = num;
    av->esq = LerArvoreAVL(fp);
    av->dir = LerArvoreAVL(fp);
    fscanf(fp," %c", &c);
    return av;
}

int altura(AVL* a){
    if(a == NULL)
        return 0;
    else{
        int he = altura(a->esq);
        int hd = altura(a->dir);
        if(he>hd)
            return he+1;
        else
            return hd+1;
    }
}

void Ajustarfb(AVL *a){
    if(a != NULL) {
        int he = altura(a->esq);
        int hd = altura(a->dir);
        a->FB = hd - he;
        Ajustarfb(a->esq);
        Ajustarfb(a->dir);
    }
}

AVL* LerAVL(FILE *f){
    AVL *a = LerArvoreAVL(f);
    Ajustarfb(a);
    return a;
}

void PreOrdem(AVL *a){
    if(a != NULL){
        printf("%d ", a->info);
        PreOrdem(a->esq);
        PreOrdem(a->dir);
    }
}

void PosOrdem(AVL* a){
    if(a != NULL){
        PosOrdem(a->esq);
        PosOrdem(a->dir);
        printf("%d ", a->info);
    }
}

void EmOrdem(AVL* a){
    if(a != NULL){
        EmOrdem(a->esq);
        printf("%d ", a->info);
        EmOrdem(a->dir);
    }
}

void ImpNivel(AVL *a,int cont, int n){
    if(a != NULL){
        if(cont == n){
            printf("%d ", a->info);
        }
        ImpNivel(a->esq,cont+1,n);
        ImpNivel(a->dir,cont+1,n);
    }
}

int AlturaAVL(AVL *a){
    if(a == NULL)
        return 0;
    else{
        int he = AlturaAVL(a->esq);
        int hd = AlturaAVL(a->dir);
        if(he > hd)
            return he + 1;
        else
            return hd + 1;
    }
}

void EmLargura(AVL *a){
    if(a != NULL){
        int  h = AlturaAVL(a);
        int cont = 0;
        for(int i = 0; i < h; i++){
            ImpNivel(a, cont, i);
        }
    }
}

void imprimirAVL(AVL* a){
    if(a != NULL){
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

int ExisteAVL(AVL *a, int x){
    if(a!=NULL){
        if(a->info == x)
            return 1;
        else{
            if(x < a->info)
                return ExisteAVL(a->esq, x);
            else if(x > a->info)
                return ExisteAVL(a->dir, x);
        }
    }
    return 0;
}

int Imp_nivel_de_x(AVL* a,int cont, int x){
    if(a != NULL){
        if(a->info == x)
            return cont;
        else{
            if(a->info > x)
                return Imp_nivel_de_x(a->esq, cont + 1, x);
            else
                return Imp_nivel_de_x(a->dir, cont + 1, x);
        }
    }
    return -1;
}

void imp_folha_mnr_x(AVL *a, int x){
    if(a != NULL){
        if(x <= a->info)
            imp_folha_mnr_x(a->esq, x);
        else if(x > a->info){
            if(a->esq == NULL && a->dir == NULL)
                printf(" %d", a->info);
            else{
                imp_folha_mnr_x(a->esq, x);
                imp_folha_mnr_x(a->dir, x);
            }
        }
    }
}

AVL *rotacaoDSimples(AVL *a){
    AVL *b = a;
    AVL *r = a->esq;
    b->esq = r->dir;
    r->dir = b;
    if(r->FB == -1){
        r->FB = 0;
        b->FB = 0;
    }
    else{
        r->FB = 1;
        b->FB = -1;
    }
    a = r;
    return a;
}

AVL *rotacaoDDupla(AVL *r){
    AVL *c = r;
    AVL *a = c->esq;
    AVL *b = a->dir;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    switch (b->FB){
        case -1:
            a->FB = 0;
            c->FB = 1;
            break;
        case 0:
            a->FB = 0;
            c->FB = 0;
            break;
        case 1:
            a->FB = -1;
            c->FB = 0;
            break;
    }
    b->FB = 0;
    r = b;
    return r;
}

AVL *rotacaodir(AVL*a){
    if(a->esq->FB == 1){
        a = rotacaoDDupla(a);
    }
    else
        a = rotacaoDSimples(a);
    return a;
}

AVL *rotacaoEDupla(AVL *r){
    AVL *c = r;
    AVL *a = c->dir;
    AVL *b = a->esq;
    c->dir = b->esq;
    a->esq = b->dir;
    b->dir = a;
    b->esq = c;
    switch (b->FB){
        case -1:
            a->FB = 0;
            c->FB = 1;
            break;
        case 0:
            a->FB = 0;
            c->FB = 0;
        case 1:
            a->FB = -1;
            c->FB = 0;
            break;
    }
    b->FB = 0;
    r = b;
    return r;
}

AVL *rotacaoESimples(AVL *a){
    AVL *r = a->dir;
    AVL *b = a;
    b->dir = r->esq;
    r->esq = b;
    if(r->FB == 1){
        r->FB = 0;
        b->FB = 0;
    }
    else{
        r->FB = -1;
        b->FB = 1;
    }
    a = r;
    return r;
}

AVL *rotacaoesq(AVL *a){
    if(a->dir->FB == -1)
        a = rotacaoEDupla(a);
    else
        a = rotacaoESimples(a);
    return a;
}

AVL* inserir(AVL* a, int x, int *hmudou){
    if(a == NULL){
        a = (AVL*)malloc(sizeof(AVL));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        *hmudou = 1;
    }
    else {
        if (x <= a->info) {
            a->esq = inserir(a->esq, x, hmudou);
            if (*hmudou == 1) {
                switch (a->FB) {
                    case -1:
                        a->FB = 0;
                        *hmudou = 0;
                        break;
                    case 0:
                        a->FB = 1;
                        *hmudou = 1;
                        break;
                    case 1:
                        a = rotacaoesq(a);
                        *hmudou = 0;
                        break;
                }
            }
        }
        else {
            a->dir = inserir(a->dir, x, hmudou);
            if (*hmudou == 1) {
                switch (a->FB) {
                    case -1:
                        a = rotacaodir(a);
                        *hmudou = 0;
                        break;
                    case 0:
                        a->FB = -1;
                        *hmudou = 1;
                        break;
                    case 1:
                        a->FB = 0;
                        *hmudou = 0;
                        break;
                }
            }
        }
    }
    return a;
}

AVL* remover(AVL *a, int x, int *hmudou){
    if(a != NULL)
    {
        if(a->info == x)
        {
            if(a->esq == NULL && a->dir == NULL)
            {
                free(a);
                *hmudou = 1;
                return NULL;
            }
            else if(a->esq == NULL || a->dir == NULL)
            {
                AVL *aux;
                if(a->esq == NULL){
                    aux = a->dir;
                }
                else{
                    aux = a->esq;
                }
                free(a);
                *hmudou = 1;
                return aux;
            }
            else
            {
                AVL* maioresq = a->esq;
                int i;
                while(maioresq->dir != NULL)
                    maioresq = maioresq->dir;
                a->info = maioresq->info;
                a->esq = remover(a->esq, a->info, hmudou);
                if(*hmudou == 1){
                    switch (a->FB)
                    {
                        case -1:
                            a->FB = 0;
                            *hmudou = 1;
                            break;
                        case 0:
                            a->FB = 1;
                            *hmudou = 0;
                            break;
                        case 1:
                            i = a->dir->FB;
                            a = rotacaoesq(a);
                            if(i == 0)
                                *hmudou = 0;
                            else
                                *hmudou = 1;
                            break;
                    }
                }
            }
        }
        else if(x < a->info)
        {
            a->esq = remover(a->esq, x, hmudou);
            int i;
            if(*hmudou == 1)
            {
                switch (a->FB)
                {
                    case -1:
                        a->FB = 0;
                        *hmudou = 1;
                        break;
                    case 0:
                        a->FB = 1;
                        *hmudou = 0;
                    case 1:
                        i = a->dir->FB;
                        a = rotacaoesq(a);
                        *hmudou = 1;
                        if(i == 0){
                            *hmudou = 0;
                        }
                        else{
                            *hmudou = 1;
                        }
                        break;
                }
            }
        }
        else
        {
            a->dir = remover(a->dir, x, hmudou);
            if(*hmudou == 1)
            {
                int i;
                switch (a->FB)
                {
                    case -1:
                        i = a->esq->FB;
                        a = rotacaodir(a);
                        if(i == 0){
                            *hmudou = 0;
                        }
                        else{
                            *hmudou = 1;
                        }
                        break;
                    case 0:
                        a->FB = -1;
                        *hmudou = 0;
                        break;
                    case 1:
                        a->FB = 0;
                        *hmudou = 1;
                }
            }
        }
    }
    return a;
}

void freeAVL(AVL *a){
    if(a != NULL){
        freeAVL(a->esq);
        freeAVL(a->dir);
        free(a);
    }
}

int main(){
    int opcao = 0; 
    AVL *a = NULL;
    while (opcao != 8){
        opcao = ImprimirOpcoes();
        if(opcao == 1){
            char caminho[100];
            printf("\nDigite o caminho do seu arquivo\n");
            fflush(stdin);
            fgets(caminho, 100, stdin);
            caminho[strcspn(caminho, "\n")] = 0;
            FILE *f = fopen(caminho, "rt");
            if(f == NULL) {
                printf("\nErro ao abrir o arquivo.\n");
                continue;
            }
            a = LerAVL(f);
            fclose(f);
        }
        if(opcao == 2){
            imprimirAVL(a);
        }
        if(opcao == 3){
            int n1;
            printf("\nDigite o elemento para verificar se existe na ABB\n");
            scanf(" %d", &n1);
            int i = ExisteAVL(a, n1);
            if(i == 1)
                printf("\nO elemento %d Existe na ABB\n", n1);
            else
                printf("\nO elemento %d NAO Existe na ABB\n", n1);
        }
        if(opcao == 4){
            int n2;
            int cont = 0;
            printf("\nDigite o elemento que deseja saber o nivel: \n");
            scanf(" %d", &n2);
            int i = Imp_nivel_de_x(a, cont, n2);
            if(i != -1)
                printf("\nNivel do elemento %d = %d\n", n2, i);
            else{
                printf("\nArvore Nula\n");
            }
        }
        if(opcao == 5){
            int n3;
            printf("\nDigite o numero para imprimir as folhas menores que ele: \n");
            fflush(stdin);
            scanf(" %d", &n3);
            imp_folha_mnr_x(a, n3);
        }
        if(opcao == 6){
            int n4;
            int hmudou = 0;
            printf("\nDigite o valor que voce quer inserir: \n");
            scanf(" %d", &n4);
            a = inserir(a, n4, &hmudou);
            PreOrdem(a);
        }
        if(opcao == 7){
            int n5, existe;
            int hmudou = 0;
            printf("\nDigite o valor que voce quer remover: \n");
            scanf(" %d", &n5);
            existe = ExisteAVL(a, n5);
            if(existe == 0)
                printf("O elemento digitado nao existe na arvore\n");
            else{
                a = remover(a, n5, &hmudou);
                if(a == NULL){
                    printf("\nNao existem elementos na arvore");
                }
                else{
                PreOrdem(a);
                }
            }
        }
        if(opcao == 8){
            freeAVL(a);
            exit(1);
        }
    }
}