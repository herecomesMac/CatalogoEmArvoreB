#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "filme.h"

// Gera o ponteiro
TMovie *inicializa() {
  return NULL;
}

// Aloca o espaço na memória e preenche o objeto
TMovie *cria_filme(char* titulo, int ano, char* diretor, char* genero, int duracao) {
  TMovie *novo = (TMovie *) malloc(sizeof(TMovie));
  strcpy(novo->titulo, titulo);
  novo->ano = ano;
  strcpy(novo->diretor, diretor);
  strcpy(novo->genero, genero);
  novo->duracao = duracao;

  return novo;
}

void imprime_info(TMovie *filme){
  printf("Titulo: %s \n", filme->titulo);
  printf("---Ano de Lancamento: %i \n", filme->ano);
  printf("---Diretor: %s \n", filme->diretor);
  printf("---Genero: %s \n", filme->genero);
  printf("---Duracao: %i \n",filme->duracao);
}
