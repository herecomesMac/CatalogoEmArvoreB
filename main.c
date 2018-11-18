#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "filme.h"

typedef struct no{
  TMovie *movie;
  int quantaschaves; //quantidades de chaves no nó
  struct TNo *ponteiro_pai; //ponteiro para o pai
  int *arraydechaves; //array de chaves
  struct TNo **filhos; //ponteiro para o array de ponteiros
}TNo;

TNo *inicializa() {
    return NULL;
}

TNo *cria_no(char *nomedoarquivo) {
  FILE *arq = fopen(nomedoarquivo, "r");
  int cont = 0;
  if(!arq){
    exit(1);
  }
  TNo *novo = (TNo *) malloc(sizeof(TNo));
  char c = fgetc(arq);
  while(c != '/'){
    novo->movie->titulo[cont] = c;
    c = fgetc(arq);7
    cont++;
  }
  cont = 0;
  char ano = fgetc(arq);
  char anocompleto[4];
  while(ano != '/'){
    anocompleto[cont] = ano;
    ano = fgetc(arq);
    cont++;
  }
  novo->movie->ano = atoi(anocompleto);
  cont = 0;
  c = fgetc(arq);
  while(c != '/'){
    novo->movie->diretor[cont] = c;
    c =fgetc(arq);
    cont++;
  }
  cont = 0;
  c = fgetc(arq);
  while(c != '/'){
    novo->movie->genero[cont] = c;
    c = fgetc(arq);
    cont++;
  }
  cont = 0;
  char dur = fgetc(arq);
  char duracao[4];
  while(dur != '\n'){
    duracao[cont] = dur;
    dur = fgetc(arq);
    cont++;
  }
  novo->movie->duracao = atoi(duracao);

  imprime_info(novo->movie);
  fclose(arq);
  return novo;
}


int main(){
  TNo *raiz = inicializa();
  raiz = cria_no("filmes.txt");
  return 0;
}
