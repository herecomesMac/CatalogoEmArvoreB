#ifndef ARVORE_H
#define ARVORE_H

#include<stdio.h>
#include<string.h>
#include "filme.h"

typedef struct No{
  TMovie *movie;
  int quantaschaves; //quantidades de chaves no nó
  struct No *ponteiro_pai; //ponteiro para o pai
  int *arraydechaves; //array de chaves
  struct No **filhos; //ponteiro para o array de ponteiros
}TNo;

// Gera um ponteiro, apenas
TNo *inicializa_no();

//Faz a mesma coisa que os strsep, porém como não funcionou, fiz uma função própria.
char* mystrsep(char** stringp, const char* delim);

//TO-DO
// Cria de verdade um nó e preenche, recebe a linha lida como input
TNo *cria_da_linha(char*);

//TO-DO
// recebe um input do usuario e cria um no com ele
TNo *cria_do_input(char*);

//TO-DO
// Busca um nó pela sua chave primária
int busca(char *titulo, int ano, FILE *meta, FILE *dados, int *pont, int *encontrou);

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

//Tamanho do Nó para fazer fseek mais fácil
int tamanho_No(int D);


#endif
