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

int somar(Lista* l){
    if(l == NULL)   
        return 0;
    else    
        return l->data + somar(l->next);
}

int main(){
    Lista* lista = new_item(10);
    lista = push_front(lista, 100);
    lista = push_front(lista, 1000);
    lista = push_front(lista, 10000);

    int resultado = somar(lista);
    printf("%d ", resultado);
}

