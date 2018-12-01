#ifndef LISTA_FILMES_H
#define LISTA_FILMES_H

#include "filme.h"

typedef struct ListaFilmes{
    Filme *fi;
    struct ListaFilmes *prox;
}ListaFilmes;


ListaFilmes *insere_lista(ListaFilmes *lista, Filme *fi);

void imprime_lista(ListaFilmes *lista);


#endif