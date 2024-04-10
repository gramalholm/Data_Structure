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

int num_contagem(Lista* l, int x){
    if(l == NULL)
        return 0;
    else if(l->data == x)
        return 1 + num_contagem(l->next, x);
    else 
        return num_contagem(l->next, x);
}

int main(){
    Lista* lista = new_item(10);
    lista = push_front(lista, 6);
    lista = push_front(lista, 8);
    lista = push_front(lista, 5);
    lista = push_front(lista, 6);
    lista = push_front(lista, 9);
    lista = push_front(lista, 44);
    lista = push_front(lista, 6);
    lista = push_front(lista, 6);

    int resultado = num_contagem(lista, 44);
    printf("%d ", resultado);
}

