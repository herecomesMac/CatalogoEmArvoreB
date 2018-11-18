#include<stdio.h>
#include<stdlib.h>
#include "filme.h"

void imprime_info(TMovie *filme){
  printf("Titulo: %s \n", filme->titulo);
  printf("Ano de Lancamento: %i \n", filme->ano);
  printf("Diretor: %s \n", filme->diretor);
  printf("Genero: %s \n", filme->genero);
  printf("Duracao: %i \n",filme->duracao);
}
