#ifndef ARVORE_H
#define ARVORE_H

#include<stdio.h>
#include<string.h>
#include "filme.h"
#include "index.h"


typedef struct No{
  int n_chaves; // quantidades de chaves no nó
  int end_pai; // ponteiro para o pai
  char **array_chaves; // array de chaves
  int *end_filhos; // array de endereço dos filhos
  TMovie **filmes; // dados dos filhos
}TNo;

// Gera um nó sem dados
TNo *cria_no(int);

//Tamanho do Nó para fazer fseek mais fácil
int tamanho_No(int);

//TO-DO
// recebe um input do usuario e cria um no com ele
TNo *cria_do_input(char*);

// Busca um nó pela sua chave primária
int busca(char *chave, Index *index, int pos, int*);

//Le o no
TNo *le_no(Index *index, int pos);

//Libera no
void libera_no(TNo *no, int o);

// TO-DO
// Percorre todos os nós da árvore a partir do primeiro e retorna uma fila de nós
// daquele diretor
void busca_por_diretor(char* diretor, Index *index);

//TO-DO
// insere um nó na árvore
int insere_filme(Index *index, TMovie *filme);

int insere_simples(Index*, TNo*, int, TMovie*);

int insere_com_distribuicao(Index*, TNo*, int, TMovie*);

// TO-DO
// recebe uma have e remove o nó com aquela chave da árvore
TNo *remove_no(char*);

//Salva o nó
<<<<<<< HEAD
void salva_no(TNo *no, Index *index);
=======
void *salva_no(TNo *no, Index *index, int pos);
>>>>>>> 53be34f6ff5dfc857fe53688ab2178c99b1baf3f

#endif
