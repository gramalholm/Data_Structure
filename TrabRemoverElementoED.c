#include<stdlib.h>
#include<stdio.h>

typedef struct Lista{
	int data;
	struct Lista* next;
}Lista;

Lista* new_item(int i){
	Lista* l = (Lista*)malloc(sizeof(Lista));
	l->data = i;
	l->next = NULL;
  return l;
}

Lista* push_front(Lista* l, int i){
	Lista* new_head = new_item(i);
	new_head->next = l;
	return new_head;
}

void remov_elemento(Lista* l, int x){ 
    if(l!=NULL){
        if(l->data == x){
            Lista* no_auxiliar = l->next;
            l->data = no_auxiliar->data;
            l->next = no_auxiliar->next;
        }
        else{
            remov_elemento(l->next, x);
        }
    }
}

void imprimir(Lista* l){
  if(l!=NULL)
   {
     printf("%d ", l->data);
     imprimir(l->next);
    }
}

int main(){
    Lista* lista = new_item(10);
    lista = push_front(lista, 8);
    lista = push_front(lista, 6);
    lista = push_front(lista, 5);

    remov_elemento(lista, 6);
    imprimir(lista);
}