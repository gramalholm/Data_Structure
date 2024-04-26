#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10

typedef struct Student{
    int mat;
    char name[100];
    char course[50];
}Student;

typedef struct Register{
    Student *st;
    int availability;
}Register;

int menu(){
    int opcao = 0;
    printf("\nDigite a opcao desejada: \n");
    printf("1.Inserir novo aluno\n");
    printf("2.Imprimir dados do aluno\n");
    printf("3.Imprimir tabela de dispersão\n");
    printf("4.Sair\n");
    scanf("%d", &opcao);
    return opcao;
}

void initialize_file(char *path){
    FILE *f = fopen(path, "wb");
    Register r;
    int i;
    r.availability = 1;
    for(i = 0; i<N; i++){
        fwrite(&r, sizeof(Register), 1, f);
    }
    fclose(f);
}

int hash(int key, int size){
    key = key%1000;
    return key%size;
}

int find_position(char *path, int x){
    int pos = hash(x, N);
    Register r;
    FILE *f = fopen(path, "rb");
    fseek(f, pos*sizeof(Register), SEEK_SET);
    fread(&r,sizeof(Register), 1, f);
    while(r.availability == 0){
        pos = (pos+1)%N;
        fseek(f, pos*sizeof(Register), SEEK_SET);
        fread(&r,sizeof(Register), 1, f);
    }
    fclose(f);
    return pos;
}

Student * createStudent(int mat, char *nam, char *cou){
    Student *s = (Student*)malloc(sizeof(Student));
    s->mat = mat;
    strcpy(s->name, nam);
    strcpy(s->course, cou);
    return s;
}

void insert(char *path, Student *s){
    int pos = find_position(path, s->mat);
    FILE *arq = fopen(path,"r+b");
    Register r;
    r.st = s;
    r.availability = 0;
    fseek(arq, pos*sizeof(Register), SEEK_SET);
    fwrite(&r, sizeof(Register), 1 , arq);
    fclose(arq);
}

void print_student(char *path, int x){
    int pos = hash(x, N);
    FILE *f = fopen(path, "rb");
    Register r;
    fseek(f,pos*sizeof(Register), SEEK_SET);
    fread(&r, sizeof(Register), 1, f);
    if(r.availability == 0){
        printf("Dados do Aluno: \n");
        printf("Matricula: %d ", r.st->mat);
        printf("Nome: %s ", r.st->name);
        printf("Curso: %s\n", r.st->course);
    }
    else    
        printf("Aluno nao encontrado\n");
    fclose(f);
}

void print_hashing(char *path){
    FILE *f = fopen(path, "rb");
    Register a;
    for(int i = 0; i < N; i++)
    {
        fseek(f, i*sizeof(Register), SEEK_SET);
        fread(&a, sizeof(Register), 1, f);
        if(a.availability == 0){
            printf("[%d]Dados do aluno: Nome %s, matricula: %d, curso: %s \n", i, a.st->name, a.st->mat, a.st->course);
        }
        else
            printf("[%d]Disponivel \n", i);
    }
    fclose(f);
}

int main(){
    int opc;
    char path[100];
    printf("Digite o caminho do seu arquivo: \n");
    fflush(stdin);
    scanf(" %99[^\n]", path);
    scanf("%*c");
    initialize_file(path);
    while(opc!=4){
        opc = menu();
        if(opc == 1){
            int mat;
            char name[100];
            char course[50];
            Student *a;
            printf("Digite os dados do aluno:\n");
            fflush(stdin);
            printf("Nome: \n");
            scanf(" %[^\n]", name);
            fflush(stdin);
            printf("Curso: \n");
            scanf(" %[^\n]", course);
            fflush(stdin);
            printf("Matricula: \n");
            scanf(" %d", &mat);
            a = createStudent(mat,name,course);
            insert(path, a);
            printf("Aluno inserido! \n");
        }
        if(opc == 2){
            int mat;
            printf("Digite a Matricula do aluno: \n");
            scanf("%d", &mat);
            print_student(path, mat);
        }
        if(opc == 3){
            print_hashing(path);
        }
        if(opc == 4){
            exit(0);
        }
    }
}