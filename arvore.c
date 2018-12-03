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
  no->array_chaves = (char **)malloc(sizeof(char)*85* (2*o));
  no->end_filhos = (int *) malloc(sizeof(int) * (2*o+1));
  no->filmes = (TMovie **) malloc(sizeof(TMovie *) * (2*o));

  for(int i = 0; i< (2*o); i++) {
    no->end_filhos[i] = -1;
    no->array_chaves[i] = NULL;
    no->filmes[i] = NULL;
  }
  no->end_filhos[2*o+1] = -1;
  return no;
}

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
  size_t buffer_size = tamanho_no(index->ordem);
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
    fread(&no->array_chaves[0], sizeof(int), 1, arv);
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

void *salva_no(TNo *no, Index *index, int pos){
>>>>>>> 53be34f6ff5dfc857fe53688ab2178c99b1baf3f
  int i;
  FILE *arv = fopen(index->arvore, "wb");
  fseek(arv, pos, SEEK_SET);

  fwrite(&no->n_chaves, sizeof(int), 1, arv);
  fwrite(&no->end_pai, sizeof(int), 1, arv);

  // escreve todas as chaves no arquivo
  for(int i=0; i< (2*index->ordem); i++) {
    fwrite(&no->array_chaves[i], sizeof(int), 1, arv);
  }

  // escreve todos os filhos no arquivo
  for(int i=0; i< (2*index->ordem+1); i++) {
    fwrite(&no->end_filhos[i], sizeof(int), 1, arv);
  }

  // escreve todos os filmes no arquivo
  TMovie *vazio = cria_filme("", -1, "", "", -1);
  for (i = 0; i < (2*index->ordem); i++) {
      if (no->filmes[i]) {
        fwrite(no->filmes[i]->titulo, sizeof(char), sizeof(char)*80, arv);
        fwrite(&no->filmes[i]->ano, sizeof(int), 1, arv);
        fwrite(no->filmes[i]->diretor, sizeof(char), sizeof(char)*50, arv);
        fwrite(no->filmes[i]->genero, sizeof(char), sizeof(char)*30, arv);
        fwrite(&no->filmes[i]->duracao, sizeof(int), 1, arv);
      } else {
        fwrite(vazio->titulo, sizeof(char), sizeof(char)*80, arv);
        fwrite(&vazio->ano, sizeof(int), 1, arv);
        fwrite(vazio->diretor, sizeof(char), sizeof(char)*50, arv);
        fwrite(vazio->genero, sizeof(char), sizeof(char)*30, arv);
        fwrite(&vazio->duracao, sizeof(int), 1, arv);
      }
  }
<<<<<<< HEAD
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

  free(vazio);
  libera_no(no, index->ordem);
  fclose(arv);

}

int busca(char *chave, Index *index, int pos, int* achou) {

// a árvore ainda está vazia
  if(index->prox_pos_livre = 0) {
    achou = 0;
    return 0;
  }

  // lẽ o nó para a memória
  TNo *no = le_no(index, pos);
  // checa se a chave está ali ou em um dos filhos
  for (int i = 0; i < 2 * index->ordem; i++) {
      // printf("%d, %s\n", i, no->);
  }


}

int insere_filme(Index *index, TMovie *filme) {
  // printf("Inserindo o filme %s\n", filme->titulo);
  // printf("Buscando pela chave do filme (%s) na biblioteca...\n", filme->chave);
  // busca a posição do nó onde o filme deveria estar, começando pela raiz
  int *achou = 0;
  int pos_no = busca(filme->chave, index, index->pont_raiz, achou);

  // lê o nó naquela posição para a memória
  TNo *no = le_no(index, pos_no);
  // se a chave já está no nó, retorna erro
  if(achou != 0) {
    printf("Você tentou inserir uma chave que já existe\n");
    return 1;
  }

  // se tiver espaço, insere o filme e reescreve o nó
  if(no->n_chaves <= (2*index->ordem)) {
    printf("n chaves %d\n", no->n_chaves);
    return insere_simples(index, no, pos_no, filme);
  }

  // se nao tiver espaço
  return insere_com_distribuicao(index, no, pos_no, filme);
}

int insere_simples(Index* index, TNo* no, int pos, TMovie *filme) {
  printf("insere_simples\n");
  // se nao tem filhos, só inserir chaves na posição certa
  char *chave = filme->chave;
  if(no->end_filhos[0] == -1) {
    printf("sem filhos\n");

    // vou movendo as chaves para frente da última para a primeira paro na primeira chave
    // que for menor que a minha
    int i = no->n_chaves;
    if (no->array_chaves[i]) {
      while(i >= 0 && strcmp(no->array_chaves[i], filme->chave) > 0) {
        no->array_chaves[i+1] = no->array_chaves[i];
        no->filmes[i+1] = no->filmes[i];
        i--;
      }
    }

    // agora que movi todas as chaves maiores pra frente, posso inserir
    no->array_chaves[i] = filme->chave;
    no->filmes[i] = filme;
    no->n_chaves++;
    index->qtd_filmes++;
    printf("%s\n", no->array_chaves[i]);

    salva_no(no, index, pos);
    return 0;
  }

  //se tiver filhos
}

int insere_com_distribuicao(Index* index, TNo* no, int pos, TMovie *filme) {
  printf("insere_com_distribuicao\n");

  return 0;
}
