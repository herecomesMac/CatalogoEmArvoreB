#ifndef FILME_H
#define FILME_H

#include<stdio.h>

typedef struct filme{
  char titulo[80]; //titulo do filme
  int ano; //ano de lançamento
  char diretor[50]; //nome do diretor
  char genero[30]; //gênero do filme
  int duracao; //duração
}TMovie;

// Imprime info do nó
void imprime_info(TMovie*);


#endif // FILME_H
