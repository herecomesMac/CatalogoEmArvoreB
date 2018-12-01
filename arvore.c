#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "arvore.h"
// #include "filme.h"

int tamanho_No(int D){
  return sizeof(int) + // m
    sizeof(int) + // pont_pai
    sizeof(int) * (2 * D + 1) + // p
    tamanho_filme() * (2 * D); // filmes
}

int busca(char *titulo, int ano, FILE *meta, FILE *dados, int *pont, int *encontrou){
    Metadados *temp = le_metadados(meta);
    *pont = temp->pont_raiz;
    *encontrou = 0;
    fseek(dados, temp->pont_raiz, SEEK_SET);
    int atual = temp->pont_raiz;
    free(temp);
    No *no = le_no(dados);

    int reset = 0;
    int pos = 0;
    int fim = 0;
    int i = 0;
    while(i < no->m && fim != 1){
        if(strcmp(titulo, no->filmes[i]->titulo) == 0){
            if(ano == no->filmes[i]->ano) {
                fim = 1;
                *encontrou = 1;
                *pont = atual;
                pos = i;
            }
        } else if (strcmp(titulo, no->filmes[i]->titulo) < 0){
            if(no->p[i] != -1){
                fseek(dados, no->p[i], SEEK_SET);
                atual = no->p[i];
                no = le_no(dados);
                reset = 1;
            }else{
                fim = 1;
                *encontrou = 0;
                *pont = atual;
                pos = i;
            }
        } else if ( i == (no->m - 1)){
            if(no->p[i+1] != -1){
                fseek(dados, no->p[i+1], SEEK_SET);
                atual = no->p[i+1];
                no = le_no(dados);
                reset = 1;
            }else{
                fim = 1;
                *encontrou = 0;
                *pont = atual;
                pos = i + 1;
            }
        }
        i++;
        if(reset == 1){
            i = 0;
            reset = 0;
        }
    }

    libera_no(no);
    return pos;
}


// TO-DO: criar o resto das variáveis!
// Cria de verdade um nó e preenche, recebe a linha lida como input
TNo *cria_da_linha(char *linha) {
  char *titulo, *diretor, *genero;
  int ano, duracao;
  TNo *novo = (TNo *)malloc(sizeof(TNo));

  char* mystrsep(char** stringp, const char* delim){

    char* start = *stringp;
    char* p;

    p = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (p == NULL)
    {
      *stringp = NULL;
    }
    else
    {
      *p = '\0';
      *stringp = p + 1;
    }

    return start;
}

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

  TMovie *filme = cria_filme(titulo, ano, diretor, genero, duracao);
  novo->movie = filme;
  novo->quantaschaves= 0;
  novo->ponteiro_pai = NULL;
  novo->arraydechaves = (int *) malloc(sizeof(int *) * (d * 2));
  novo->filhos = (TNo **) malloc(sizeof(TNo *) * (d * 2) + 1);
  for (int i = 0; i < (d * 2 + 1); i++) {
      novo->filhos[i] = NULL;
  return novo;
}

void insere_no(TNo *arv, TNo *no) {
  printf("To be implemented\n");
  return;
}
