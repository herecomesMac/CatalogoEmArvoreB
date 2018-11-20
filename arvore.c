#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "arvore.h"
// #include "filme.h"

TNo *inicializa_no() {
    return NULL;
}

// typedef struct no{
//   TMovie *movie;
//   int quantaschaves; //quantidades de chaves no nó
//   struct TNo *ponteiro_pai; //ponteiro para o pai
//   int *arraydechaves; //array de chaves
//   struct TNo **filhos; //ponteiro para o array de ponteiros
// }TNo;

// TO-DO: criar o resto das variáveis!
// Cria de verdade um nó e preenche, recebe a linha lida como input
TNo *cria_da_linha(char *linha) {
  char *titulo, *diretor, *genero;
  int ano, duracao;
  TNo *novo = (TNo *)malloc(sizeof(TNo));

  // separando a string e preenchendo as variáveis com os valores
  char* palavra;
  for (size_t i = 0; i < 5; i++) {
    palavra = strsep(&linha, "/");
    switch (i) {
      case 0:
        titulo = palavra;
        break;

      case 1:
        ano = atoi(palavra);
        break;

      case 2:
        diretor = palavra;
        break;

      case 3:
        genero = palavra;
        break;

      case 4:
        duracao = atoi(palavra);
        break;
    }
  }
  TMovie *filme = cria_filme(titulo, ano, diretor, genero, duracao);
  novo->movie = filme;
  return novo;
}

void insere_no(TNo *arv, TNo *no) {
  printf("To be implemented\n");
  return;
}
