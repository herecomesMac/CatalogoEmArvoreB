#ifndef ARVORE_H
#define ARVORE_H

#include<stdio.h>
#include<string.h>
#include "filme.h"

typedef struct No{
  int n_chaves; // quantidades de chaves no nó
  int end_pai; // ponteiro para o pai
  int *array_chaves; // array de chaves
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
int busca(char *titulo, int ano, FILE *meta, FILE *dados, int *pont, int *encontrou);

//Le o no
TNo *le_no(FILE *in);

//Libera no
void libera_no(TNo *no, int o);

// TO-DO
// Percorre todos os nós da árvore a partir do primeiro e retorna uma fila de nós
// daquele diretor
TNo *busca_por_diretor(char*);

//TO-DO
// insere um nó na árvore
void insere_no(TNo*, TNo*, int);

// TO-DO
// recebe uma have e remove o nó com aquela chave da árvore
TNo *remove_no(char*);

#endif
