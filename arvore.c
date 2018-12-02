#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "arvore.h"
#include "filme.h"

/* typedef struct No{
  int n_chaves; // quantidades de chaves no nó
  int end_pai; // ponteiro para o pai
  int *array_chaves; // array de chaves
  int *end_filhos; // array de endereço dos filhos
  TMovie **filmes; // dados dos filhos
}TNo; */

TNo *cria_no(int o) {
  TNo *no = (TNo *) malloc(sizeof(TNo));
  no->n_chaves = 0;
  no->end_pai = -1;
  no->array_chaves = (int *) malloc(sizeof(char[85]) * (2*o));
  no->end_filhos = (int *) malloc(sizeof(int) * (2*o+1));
  no->filmes = (TMovie **) malloc(sizeof(TMovie *) * (2*o+1));
}

// checada
int tamanho_No(int o){
  return sizeof(int) + // m
    sizeof(int) + // pont_pai
    sizeof(int) * (2 * o + 1) + // p
    tamanho_filme() * (2 * o); // filmes
}

void libera_no(TNo *no, int o) {
    for (int i = 0; i < 2 * o; i++) {
        free(no->filmes[i]);
    }
    free(no);
}
//
// No *le_no(FILE *in) {
//     int i;
//     TNo *no = (TNo *) malloc(sizeof(TNo));
//     if (0 >= fread(&no->m, sizeof(int), 1, in)) {
//         free(no);
//         return NULL;
//     }
//     fread(&no->pont_pai, sizeof(int), 1, in);
//     no->p = (int *) malloc(sizeof(int) * (2 * D + 1));
//     no->filmes = (Filme **) malloc(sizeof(Filme *) * 2 * D);
//
//     fread(&no->p[0], sizeof(int), 1, in);
//     for (i = 0; i < no->m; i++) {
//         no->filmes[i] = le_filme(in);
//         fread(&no->p[i + 1], sizeof(int), 1, in);
//     }
//
//     // Termina de ler dados nulos para resolver problema do cursor
//     // Dados lidos sao descartados
//     Filme *vazio;
//     int nul = -1;
//     for (i = no->m; i < 2 * D; i++) {
//         no->filmes[i] = NULL;
//         vazio = le_filme(in);
//         fread(&no->p[i + 1], sizeof(int), 1, in);
//         free(vazio);
//     }
//     libera_no(no);
//     return no;
// }

// int busca(char *titulo, int ano, FILE *meta, FILE *dados, int *pont, int *encontrou){
//     Metadados *temp = le_metadados(meta);
//     *pont = temp->pont_raiz;
//     *encontrou = 0;
//     fseek(dados, temp->pont_raiz, SEEK_SET);
//     int atual = temp->pont_raiz;
//     free(temp);
//     TNo *no = le_no(dados);
//
//     int reset = 0;
//     int pos = 0;
//     int fim = 0;
//     int i = 0;
//     while(i < no->m && fim != 1){
//         if(strcmp(titulo, no->filmes[i]->titulo) == 0){
//             if(ano == no->filmes[i]->ano) {
//                 fim = 1;
//                 *encontrou = 1;
//                 *pont = atual;
//                 pos = i;
//             }
//         } else if (strcmp(titulo, no->filmes[i]->titulo) < 0){
//             if(no->p[i] != -1){
//                 fseek(dados, no->p[i], SEEK_SET);
//                 atual = no->p[i];
//                 no = le_no(dados);
//                 reset = 1;
//             }else{
//                 fim = 1;
//                 *encontrou = 0;
//                 *pont = atual;
//                 pos = i;
//             }
//         } else if ( i == (no->m - 1)){
//             if(no->p[i+1] != -1){
//                 fseek(dados, no->p[i+1], SEEK_SET);
//                 atual = no->p[i+1];
//                 no = le_no(dados);
//                 reset = 1;
//             }else{
//                 fim = 1;
//                 *encontrou = 0;
//                 *pont = atual;
//                 pos = i + 1;
//             }
//         }
//         i++;
//         if(reset == 1){
//             i = 0;
//             reset = 0;
//         }
//     }
//
//     libera_no(no);
//     return pos;
// }

  // TMovie *filme = cria_filme(titulo, ano, diretor, genero, duracao);
  // novo->movie = filme;
  // novo->quantaschaves= 0;
  // novo->ponteiro_pai = NULL;
  // novo->arraydechaves = (int *) malloc(sizeof(int *) * (d * 2));
  // novo->filhos = (TNo **) malloc(sizeof(TNo *) * (d * 2) + 1);
  // for (int i = 0; i < (d * 2 + 1); i++) {
  //     novo->filhos[i] = NULL;
  // return novo;
// }

void insere_no(TNo *arv, TNo *no, int o) {
  printf("To be implemented\n");
  return;
}
