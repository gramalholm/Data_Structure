#ifndef fila_h
typedef struct fila *Fila;
int inserir(Fila f, int x);
int remover(Fila f, int *x);
void impFila(Fila f);
Fila inicializar();
Fila destruir(Fila f);
#endif