#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "arvore.h"
#include "filme.h"
#include "index.h"

TNo *cria_no(int o) {
  TNo *no = (TNo *) malloc(sizeof(TNo));
  no->n_chaves = 0;
  no->end_pai = -1;
  no->end_filhos = (int *) malloc(sizeof(int) * (2*o+1));
  no->filmes = (TMovie **) malloc(sizeof(TMovie *) * (2*o));

  for(int i=0; i< (2*o); i++) {
    no->end_filhos[i] = -1;
    no->filmes[i] = NULL;
  }
  return no;
}

// checada
int tamanho_no(int o){
  return sizeof(int) + // m
    sizeof(int) + // pont_pai
    sizeof(int) * (2 * o + 1) + // end_filhos
    tamanho_filme() * (2 * o); // filmes
}

void libera_no(TNo *no, int o) {
    for (int i = 0; i < 2 * o; i++) {
        free(no->filmes[i]);
    }
    free(no);
}

TNo *le_no(Index *index, int pos) {

  int tam_no = tamanho_no(index->ordem);
  TNo *no = cria_no(index->ordem);
  FILE *arv = fopen(index->arvore, "rb");
  size_t buffer_size = tam_no;
  char* buffer = (char *)malloc(buffer_size);

  if(buffer == NULL || !index) {
    printf("Sem espaço na memória :(\n");
    exit(1);
  }

  fseek(arv, pos*tam_no, SEEK_SET);
  fread(&no->n_chaves, sizeof(int), 1, arv);

  // se tenho coisas naquela linha, vou ler. Se não, retorno o nó vazio mesmo
  if (no->n_chaves <= 0) {
    int i;
    fread(&no->end_pai, sizeof(int), 1, arv);
    fread(&no->end_filhos[0], sizeof(int), 1, arv);
    for (i = 0; i < no->n_chaves; i++) {
        no->filmes[i] = le_filme(arv);
        fread(&no->end_filhos[i + 1], sizeof(int), 1, arv);
    }

    // Termina de ler dados nulos para resolver problema do cursor
    // Dados lidos sao descartados
    TMovie *vazio;
    int nul = -1;
    for (i = no->n_chaves; i < 2 * index->ordem; i++) {
        no->filmes[i] = NULL;
        vazio = le_filme(arv);
        fread(&no->end_filhos[i + 1], sizeof(int), 1, arv);
        free(vazio);
    }
  }

  fclose(arv);
  return no;
}

void salva_no(TNo *no, Index *index){
  int i;
  FILE *arv = fopen(index->arvore, "wb");
  fwrite(&no->n_chaves, sizeof(int), 1, arv);
  fwrite(&no->end_pai, sizeof(int), 1, arv);
  //garantidamente, sempre havera pelo menos 1 chave no noh
  //portanto, p0 sempre vai existir
  fwrite(&no->end_filhos[0], sizeof(int), 1, arv);
  TMovie *vazio = cria_filme("", -1, "", "", -1);

  for (i = 0; i < 2 * index->ordem; i++) {
      if (no->filmes[i]) {
          salva_filme(no->filmes[i], index);
      } else {
          salva_filme(vazio, index);
      }
      fwrite(&no->end_filhos[i + 1], sizeof(int), 1, arv);
  }
  free(vazio);
  fclose(arv);
}

int altera(char *titulo, int ano, Index *index){
  FILE *arv = fopen(index->arvore, "rb");
  char *nome = cria_chave(titulo, ano);
  int end;
  int *encontrou = 0;
  end = busca(nome, index, 0, encontrou);
  if(!encontrou){
      printf("O filme que desejas alterar nao existe");
      return 0;
  }
  fseek(arv, end, SEEK_SET);
  TMovie* buscado = le_filme(arv);
  imprime_info(buscado);
  char novo_Diretor[50], novo_genero[50];
  int nova_dur;
  printf("Digite o novo diretor: ");
  scanf("%[^\n]s ",novo_Diretor);
  printf("Digite o novo genero: ");
  scanf("%[^\n]s ",novo_genero);
  printf("Digite a nova duracao: ");
  scanf("%i", &nova_dur);
  int y;
  for(y=0; y<50;y++){
      buscado->diretor[y] = novo_Diretor[y];
      buscado->genero[y] = novo_genero[y];
  }
  buscado->duracao = nova_dur;
  salva_filme(buscado, index);
  free(buscado);
  return 1;
}

//vai percorrer todo o arquivo buscando no por no pelo Diretor
void busca_por_diretor(char* diretor, Index *index){
  FILE *arv = fopen(index->arvore, "rb");
  int i = 0;
  TNo *no_lido = le_no(index, i);
  while(no_lido != NULL){
    int j;
    for(j=0; j<no_lido->n_chaves;j++){
      if(strcmp(diretor, no_lido->filmes[j]->diretor)==0){
        imprime_info(no_lido->filmes[j]);
      }
    }
    i++;
    no_lido = le_no(index, i*tamanho_no(index->ordem));
  }
}

/*int busca(char *chave, Index *index, int pos) {

// a árvore ainda está vazia
  if(index->prox_pos_livre = 0) {
    return 0;
  }

  // lẽ o nó para a memória
  TNo *no = le_no(index, pos);
  // checa se a chave está ali ou em um dos filhos
  for (int i = 0; i < 2 * index->ordem; i++) {
      // printf("%d, %s\n", i, no->);
  }


}*/

/*int insere_filme(Index *index, TMovie *filme) {
  // printf("Inserindo o filme %s\n", filme->titulo);
  // printf("Buscando pela chave do filme (%s) na biblioteca...\n", filme->chave);
  // busca a posição do nó onde o filme deveria estar, começando pela raiz
  int pos_no = busca(filme->chave, index, index->pont_raiz);

  // lê o nó naquela posição para a memória
  TNo *no = le_no(index, pos_no);
  // se a chave já está no nó, retorna erro
  for(int i=0; i < no->n_chaves; i++) {
    if(no->filmes[i]->chave == filme->chave) {
      printf("Você tentou inserir uma chave que já existe\n");
      return 1;
    }
  }

  // se tiver espaço, insere o filme e reescreve o nó
  // se nao tiver espaço
  return 0;
}*/

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
