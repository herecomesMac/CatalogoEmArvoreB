#ifndef INDEX_H
#define INDEX_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Index {
    int qtd_filmes;
    int prox_pos_livre;
    int ordem;
    char *arvore;
} Index;

// Aloca espaço na memória e inicializa um index vazio
Index *cria_index(char* arq_arv, int ordem);

// TO-DO
// Le o arquivo de dados e imprime a biblioteca
void *le_biblioteca(Index *index);

#endif
