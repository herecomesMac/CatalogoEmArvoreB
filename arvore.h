#ifndef ARVORE_H
#define ARVORE_H

#include<stdio.h>
#include "filme.h"

typedef struct no{
  TMovie *movie;
  int quantaschaves; //quantidades de chaves no nó
  struct TNo *ponteiro_pai; //ponteiro para o pai
  int *arraydechaves; //array de chaves
  struct TNo **filhos; //ponteiro para o array de ponteiros
}TNo;

// Gera um ponteiro, apenas
TNo *inicializa_no();

//TO-DO
// Cria de verdade um nó e preenche, recebe a linha lida como input
TNo *cria_da_linha(char*);

//TO-DO
// recebe um inut do usuario e cria um no com ele
TNo *cria_do_input(char*);

//TO-DO
// Busca um nó pela sua chave primária
TNo *busca_por_chave(char*);

// TO-DO
// Percorre todos os nós da árvore a partir do primeiro e retorna uma fila de nós
// daquele diretor
TNo *busca_por_diretor(char*);

//TO-DO
// insere um nó na árvore
void insere_no(TNo*, TNo*);

// TO-DO
// recebe uma have e remove o nó com aquela chave da árvore
TNo *remove_no(char*);




#endif
