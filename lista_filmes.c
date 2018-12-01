#include <stdlib.h>

#include "lista_filmes.h"
#include "filme.h"

ListaFilmes *insere_lista(ListaFilmes *lista, Filme *fi){
    ListaFilmes *aux = (ListaFilmes *) malloc(sizeof(ListaFilmes));
    aux->fi = fi;
    if(!lista)
        aux->prox = NULL;
    else
        aux->prox = lista;

    return aux;
}

void imprime_lista(ListaFilmes *lista){
    while(lista){
        imprime_filme(lista->fi);
        lista = lista->prox;
    }
}