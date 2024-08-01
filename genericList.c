#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct list{
    int tipo;
    void* item;
    struct list *next;
} Pessoa;

typedef struct aluno{
    int matricula;
    char nome[100];
    char curso[100];
    int ano;
} Aluno;

typedef struct professor{
    int matricula;
    char nome[100];
    float salario;
} Professor;
float maiorSalario = 0;
int menu(){
    int opcao = 0;
    printf("\n-------- MENU --------\n");
    printf("1. Inserir Pessoa\n");
    printf("2. Remover Pessoa pela matricula\n");
    printf("3. Buscar Pessoa pela matricula\n");
    printf("4. Contar numero de alunos de um curso\n");
    printf("5. Imprimir os professores com maior salario\n");
    printf("6. Sair\n");
    scanf("%d", &opcao);
    return opcao;
}

void inicializa(Pessoa *p){
    p->item = NULL;
    p->next = NULL;
    p->tipo = 0;
}

int existeMat(Pessoa *p, int mat){
    Pessoa *aux = p;
    while(aux != NULL){
        if(aux->tipo == 1){
            Aluno *a = (Aluno*)aux->item;
            if(a->matricula == mat)
                return 1;
        }else if(aux->tipo == 2){
            Professor *prof = (Professor*)aux->item;
            if(prof->matricula == mat)
                return 1;
        }
        aux = aux->next;
    }
    return 0;
}

//op1
Pessoa *inserir(Pessoa *pe){
    int op;
    Pessoa *aux = (Pessoa*)malloc(sizeof(Pessoa));
    printf("Digite (1) para Aluno e (2) para Professor\n");
    scanf("%d", &op);
    if(op == 1){
        Aluno *a;
        a = (Aluno*)malloc(sizeof(Aluno));
        printf("Digite a matricula do Aluno\n");
        scanf("%d", &a->matricula);
        while(existeMat(pe, a->matricula)){
            printf("Matricula ja existente, tente novamente\n");
            scanf("%d", &a->matricula);
        }
        printf("Digite o nome do Aluno\n");
        scanf(" %[^\n]", a->nome);
        printf("Digite o curso do Aluno\n");
        scanf(" %[^\n]", a->curso);
        printf("Digite o ano de ingresso do Aluno\n");
        scanf(" %d", &a->ano);
        aux->item = a;
        aux->tipo = 1;
    }else if(op == 2){
        Professor *p = (Professor*)malloc(sizeof(Professor));
        printf("Digite a matricula do Professor\n");
        scanf("%d", &p->matricula);
        while(existeMat(pe, p->matricula)){
            printf("Matricula ja existente, tente novamente\n");
            scanf("%d", &p->matricula);
        }
        printf("Digite o nome do Professor\n");;
        scanf(" %[^\n]", p->nome);
        printf("Digite o salario do Professor\n");
        scanf("%f", &p->salario);
        aux->item = p;
        aux->tipo = 2;
    }
    aux->next = pe;
    return aux;
}

//op2
Pessoa *remover(Pessoa *p, int matricula){
    if(p!=NULL){
        if(p->tipo == 1){
            Aluno *a = (Aluno*)p->item;
            if(a->matricula == matricula){
                Pessoa *pe = p->next;
                free(p);
                return pe;
            }else{
                p->next = remover(p->next, matricula);
            }
        }else if(p->tipo == 2){
            Professor *prof = (Professor*)p->item;
            if(prof->matricula == matricula){
                Pessoa *pe = p->next;
                free(p);
                return pe;
            }else{
                p->next = remover(p->next, matricula);
            }
        }
    }
    printf("pessoa de matricula %d removida com sucesso\n", matricula);
    return p;
}

//op3
void buscaMatricula(Pessoa *p, int mat){
    Pessoa *aux = p;
    while(aux!=NULL){
        if(aux->tipo == 1){
            Aluno *a = (Aluno*)aux->item;
            if(a->matricula == mat){
                printf("Nome do Aluno: %s, matricula: %d, curso: %s, ano de ingresso: %d\n", a->nome, a->matricula ,a->curso , a->ano);
                break;
            }
        }else if(aux->tipo == 2){
            Professor *prof = (Professor*)aux->item;
            if(prof->matricula == mat){
                printf("Nome do Professor: %s, matricula: %d, salario: %.f\n", prof->nome, prof->matricula , prof->salario);
                break;
            }
        }
        aux = aux->next;
    }
    
}

//op4
int contaAlunosCurso(Pessoa *p, char* curso){
    Pessoa *aux = p;
    int cont = 0;
    while(aux != NULL){
        if(aux->tipo == 1){
            Aluno *a = (Aluno*)aux->item;
            if(strcmp(a->curso, curso) == 0){
                cont++;
            }
        }
        aux = aux->next;
    }
    return cont;
}

//op5
void impMaiorSalario(Pessoa *p){
    for(Pessoa *aux = p; aux!=NULL; aux = aux->next){
        if(aux->tipo == 2){
            Professor *prof = (Professor*)aux->item;
            if(prof->salario > maiorSalario){
                maiorSalario = prof->salario;
            }
        }
    }
    for(Pessoa *aux = p; aux!=NULL; aux = aux->next){
        if(aux->tipo == 2){
            Professor *prof = (Professor*)aux->item;
            if(prof->salario == maiorSalario){
                printf("Nome do professor: %s, matricula: %d, salario: %.f\n", prof->nome, prof->matricula, prof->salario);
            }
        }
    }
}

void destruir(Pessoa *p){
    if(p != NULL){
        destruir(p->next);
        free(p->item);
        free(p);
    }
}

int main(){
    int op = 0;
    Pessoa *p = (Pessoa*)malloc(sizeof(Pessoa));
    inicializa(p);
    while(op != 6){
        op = menu();
        if(op == 1){
            p = inserir(p); 
        }
        if(op == 2){
            int matricula;
            printf("Digite a matricula da pessoa que deseja remover\n");
            scanf(" %d", &matricula);
            p = remover(p,matricula);
        }
        if(op == 3){
            int matricula;
            printf("Digite a matricula da pessoa que deseja buscar\n");
            scanf(" %d", &matricula);
            buscaMatricula(p,matricula);
        }
        if(op == 4){
            char curso[50];
            int qntA = 0;
            printf("Digite o curso que voce deseja contar os Alunos: \n");
            scanf(" %[^\n]", curso);
            qntA = contaAlunosCurso(p, curso);
            printf("%d Alunos no curso %s\n", qntA, curso);
        }
        if(op == 5){
            impMaiorSalario(p);
        }
        if(op == 6){
            destruir(p);
        }
    }
}