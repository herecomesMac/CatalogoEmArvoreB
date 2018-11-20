#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arvore.h"

TNo *cria_no(char *nomedoarquivo) {
  printf("Lendo arquivo... \n");

  //Abre o arquivo e trata caso dê erro
  FILE *arq = fopen(nomedoarquivo, "r");
  if(!arq){
    printf("Não foi possível abrir o arquivo!\n");
    exit(1);
  }
  printf("Arquivo lido!\n");

  //Lê o arquivo linha a linha e gera
  printf("Gerando a biblioteca...\n");
  size_t buffer_size = sizeof(TMovie);
  char* buffer = (char *)malloc(buffer_size);
  if(buffer == NULL) {
    printf("Sem espaço na memória :(\n");
    exit(1);
  } //declarando o tamanho da linha separado porque deu ruim
  size_t tam_linha;
  while ((tam_linha = getline(&buffer, &buffer_size, arq)) != -1) {
    cria_da_linha(buffer);
  }

  // int cont = 0;
  // TNo *novo = (TNo *) malloc(sizeof(TNo));
  // char *linha = fgetc(arq);
  // printf("char: %s\n", );
  // while(c != '/'){
  //   novo->movie->titulo[cont] = c;
  //   c = fgetc(arq);
  //   cont++;
  // }
//   cont = 0;
//   char ano = fgetc(arq);
//   char anocompleto[4];
//   while(ano != '/'){
//     anocompleto[cont] = ano;
//     ano = fgetc(arq);
//     cont++;
//   }
//   novo->movie->ano = atoi(anocompleto);
//   cont = 0;
//   c = fgetc(arq);
//   while(c != '/'){
//     novo->movie->diretor[cont] = c;
//     c =fgetc(arq);
//     cont++;
//   }
//   cont = 0;
//   c = fgetc(arq);
//   while(c != '/'){
//     novo->movie->genero[cont] = c;
//     c = fgetc(arq);
//     cont++;
//   }
//   cont = 0;
//   char dur = fgetc(arq);
//   char duracao[4];
//   while(dur != '\n'){
//     duracao[cont] = dur;
//     dur = fgetc(arq);
//     cont++;
//   }
//   novo->movie->duracao = atoi(duracao);
//
//   imprime_info(novo->movie);
//   fclose(arq);
// return novo;
}


int main(){
  TNo *raiz = inicializa_no();
  raiz = cria_no("filmes.txt");
  return 0;
}
