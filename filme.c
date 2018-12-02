#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "filme.h"

// Gera o ponteiro
TMovie *inicializa() {
  return NULL;
}

int tamanho_filme(){
  return sizeof(char[80]) +
    sizeof(int) +
    sizeof(char[50]) +
    sizeof(char[30]) +
    sizeof(int);
}

char *cria_chave(char* titulo, int ano) {
  char *chave = (char *)malloc(sizeof(char)*86);
  sprintf(chave, "%d", ano);
  strcat(chave, "-");
  strcat(chave, titulo);
  return chave;
}

// Cria de verdade um nó e preenche, recebe a linha lida como input
TMovie *cria_da_linha(char *linha) {
  char *titulo, *diretor, *genero;
  int ano, duracao;

  // separando a string e preenchendo as variáveis com os valores
  char* palavra;
  for (size_t i = 0; i < 5; i++) {
    palavra = mystrsep(&linha, "/");
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
  TMovie *novo = cria_filme(titulo, ano, diretor, genero, duracao);
  imprime_info(novo);
}

// Aloca o espaço na memória e preenche o objeto
TMovie *cria_filme(char* titulo, int ano, char* diretor, char* genero, int duracao) {
  TMovie *novo = (TMovie *) malloc(sizeof(TMovie));
  strcpy(novo->titulo, titulo);
  novo->chave = cria_chave(titulo, ano);
  novo->ano = ano;
  strcpy(novo->diretor, diretor);
  strcpy(novo->genero, genero);
  novo->duracao = duracao;

  return novo;
}

void imprime_info(TMovie *filme){
  printf("Titulo: %s \n", filme->titulo);
  printf("---Chave: %s \n", filme->chave);
  printf("---Ano de Lancamento: %i \n", filme->ano);
  printf("---Diretor: %s \n", filme->diretor);
  printf("---Genero: %s \n", filme->genero);
  printf("---Duracao: %i \n",filme->duracao);
}

char* mystrsep(char** stringp, const char* delim) {
  char* start = *stringp;
  char* p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;
  if (p == NULL) { *stringp = NULL; }
  else {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}
