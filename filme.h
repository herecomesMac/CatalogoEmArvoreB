#ifndef FILME_H
#define FILME_H

#include<stdio.h>

typedef struct filme{
  char chave[85];
  char titulo[80]; //titulo do filme
  int ano; //ano de lançamento
  char diretor[50]; //nome do diretor
  char genero[30]; //gênero do filme
  int duracao; //duração
}TMovie;

// Gera o ponteiro
TMovie *inicializa();

// Aloca o espaço na memória e preenche o objeto
TMovie *cria_filme(char* titulo, int ano, char* diretor, char* genero, int duracao);

// Imprime info do nó
void imprime_info(TMovie*);

//Tamanho do struct do Filme
int tamanho_filme();

//TO-DO
// Recebe um ponteiro para o primeiro nó da fila e imprime todos usando o imprime_info
void imprime_fila(TMovie*);

// TO-DO
// recebe o ano e o diretor e gera uma chave
char *gera_chave(char*, char*);

#endif // FILME_H
