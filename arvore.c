#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "arvore.h"
#include "filme.h"
#include "index.h"

// corrigida
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

// corrigida
int tamanho_no(int o){
  return sizeof(int) + // m
    sizeof(int) + // pont_pai
    sizeof(char)*85*(2*o) + // array_chaves
    sizeof(int) * (2 * o + 1) + // end_filhos
    tamanho_filme() * (2 * o); // filmes
}

// corrigida
void libera_no(TNo *no, int o) {
    for (int i = 0; i < 2 * o; i++) {
        free(no->filmes[i]);
        free(no->array_chaves[i]);
    }
    free(no);
}


TNo *le_no(Index *index, int pos) {
  int tam_no = tamanho_no(index->ordem);
  TNo *no = cria_no(index->ordem);
  FILE *arv = fopen(index->arvore, "rb");

  // se meu arquivo está vazio não tem nada pra ler
  int asdf = ftell(arv);
  fseek(arv, 0L, SEEK_END);
  if(ftell(arv) == 0L) {
    return no;
  }

  fseek(arv, pos, SEEK_SET);
  fread(&no->n_chaves, sizeof(int), 1, arv);

  // se tenho coisas naquela linha, vou ler. Se não, retorno o nó vazio mesmo
  if (no->n_chaves <= 0) {
    fread(&no->end_pai, sizeof(int), 1, arv);
    printf("end_pai %d\n", no->end_pai);

    // lê todo o array de chaves
    for(int i=0; i< (2*index->ordem); i++) {
      printf("lendo chave posição %d, valor %s\n", i, no->array_chaves[i]);
      fread(&no->array_chaves[i], sizeof(char)*86, 1, arv);
    }
    for(int i=0; i< (2*index->ordem+1); i++) {
      printf("lendo end_filhos posição %d, valor %i\n", i, no->end_filhos[i]);
      fread(&no->end_filhos[i], sizeof(int), 1, arv);
    }

    for(int i=0; i< (2*index->ordem); i++) {
        no->filmes[i] = le_filme(arv);
    }

    // Termina de ler dados nulos para resolver problema do cursor
    // Dados lidos sao descartados
    TMovie *vazio;
    int nul = -1;
    for (int i = no->n_chaves; i < 2 * index->ordem; i++) {
        no->filmes[i] = NULL;
        vazio = le_filme(arv);
        fread(&no->end_filhos[i + 1], sizeof(int), 1, arv);
        free(vazio);
    }
  }

  fclose(arv);
  return no;
}

void *salva_no(TNo *no, Index *index, int pos){
  int i;
  FILE *arv = fopen(index->arvore, "wb");
  fseek(arv, pos, SEEK_SET);
  printf("abriu, pos: %li\n", ftell(arv));

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

  if(pos == index->prox_pos_livre) {
    index->prox_pos_livre = ftell(arv);
  }

  free(vazio);
  libera_no(no, index->ordem);
  fclose(arv);
}

// corrigido
int altera(char *titulo, int ano, Index *index){
  FILE *arv = fopen(index->arvore, "rb");
  char *nome = cria_chave(titulo, ano);

  int *encontrou = 0;
  int end = busca(nome, index, 0, encontrou);
  if(!encontrou){
      printf("O filme que desejas alterar nao existe");
      return 1;
  }

  fseek(arv, end, SEEK_SET);
  TMovie* buscado = le_filme(arv);
  imprime_info(buscado);
  char novo_Diretor[50], novo_genero[30];
  int nova_dur;
  printf("Digite o novo diretor: ");
  scanf("%[^\n]s ",novo_Diretor);
  printf("Digite o novo genero: ");
  scanf("%[^\n]s ",novo_genero);
  printf("Digite a nova duracao: ");
  scanf("%i", &nova_dur);

  strcpy(buscado->diretor, novo_Diretor);
  strcpy(buscado->genero, novo_genero);

  buscado->duracao = nova_dur;
  salva_filme(buscado, index);
  free(buscado);
  return 0;
}

//vai percorrer todo o arquivo buscando no por no pelo Diretor e imprimindo
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
  libera_no(no_lido, index->ordem);
  fclose(arv);
}

int busca(char *chave, Index *index, int pos, int* achou) {

// a árvore ainda está vazia (única chance de eu não ter chaves no nó)
printf("prox livre: %d\n", index->prox_pos_livre);
  if(index->prox_pos_livre == 0) {
    index->pont_raiz = 0;
    return 0;
  }

  // lẽ o nó para a memória
  TNo *no = le_no(index, pos);

  // acha a posição da última chave maior ou igual à minha
  int i = 0;
  while (i < no->n_chaves && strcmp(no->array_chaves[i], chave) <= 0) {
    i++;
  }

  // a primeira chave maior ou igual à mim é a que eu buscava
  if(strcmp(no->array_chaves[i], chave) == 0) {
    *achou = 1;
    return pos;
  }

  // não achei, mas sou folha
  if(no->end_filhos[0] == -1) {
    return pos;
  }

  // continuo buscando no ponteiro da esquerda da chave atual
  return busca(chave, index, no->end_filhos[i], achou);
}

int insere_filme(Index *index, TMovie *filme) {
  printf("Inserindo o filme %s\n", filme->titulo);
  printf("Buscando pela chave do filme (%s) na biblioteca...\n", filme->chave);

  // busca a posição do nó onde o filme deveria estar, começando pela raiz
  int achou = 0;
  int *ptr_achou = &achou;
  int pos_no = busca(filme->chave, index, index->pont_raiz, ptr_achou);
  printf("pos_no %d\n", pos_no);

  // se a chave já está no nó, retorna erro
  if(achou != 0) {
    printf("Você tentou inserir uma chave que já existe\n");
    return 1;
  }

  // lê o nó naquela posição para a memória
  TNo *no = le_no(index, pos_no);

  // se tiver espaço, insere o filme e reescreve o nó
  if(no->n_chaves < (2*index->ordem)) {
    return insere_simples(index, no, pos_no, filme);
  }

  // se nao tiver espaço
  return insere_com_distribuicao(index, no, pos_no, filme);
}

int insere_simples(Index* index, TNo* no, int pos, TMovie *filme) {
  printf("insere_simples\n");
  // se nao tem filhos, só inserir chaves na posição certa
  char *chave = filme->chave;
  printf("end filho %d\n", no->end_filhos[0]);

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
  printf("Filme: %s\n", no->array_chaves[i]);

  salva_no(no, index, pos);
  return 0;
}

int insere_com_distribuicao(Index* index, TNo* no, int pos, TMovie *filme) {
  TNo *pai, *novo = cria_no(index->ordem);
  // crio um novo nó para a esquerda
  salva_no(novo, index, index->prox_pos_livre);

  // se o nó cheio for raiz
  // crio um novo nó vazio, escrevo na memória reposicionando a raiz da árvore
  // e seto o pai do nó atual para ele
  if(no->end_pai == -1) {
    TNo* nova_raiz = cria_no(index->ordem);
    index->pont_raiz = index->prox_pos_livre;
    salva_no(nova_raiz, index, index->prox_pos_livre);
    no->end_pai=index->pont_raiz;
  }
  // agora eu pego o pai ou a nova raiz
  pai = le_no(index, no->end_pai);

  TMovie *sobe;
  // insiro as d menores chaves na esquerda
  // a chave do meio vai para sobe e é inserida no pai por recursão

  return 1;
}

void salva_filme(TMovie *filme, Index *index) {
  FILE *out = fopen(index->arvore, "wb");
  fwrite(filme->titulo, sizeof(char), sizeof(filme->titulo), out);
  fwrite(&filme->ano, sizeof(int), 1, out);
  fwrite(filme->diretor, sizeof(char), sizeof(filme->diretor), out);
  fwrite(filme->genero, sizeof(char), sizeof(filme->genero), out);
  fwrite(&filme->duracao, sizeof(int), 1, out);
  fclose(out);
}

//Caso de concatenação da árvore
void concatenacao(TNo *adjacente, TNo *pai, TNo *no, int posicao_no_pai, int end_pai, Index *index,  int end_filme, int end_adjacente){

    adjacente->filmes[adjacente->n_chaves] = pai->filmes[posicao_no_pai];
    adjacente->n_chaves++;
    pai->filmes[posicao_no_pai] = NULL;
    pai->n_chaves--;
    int i;
    for(i = 0; i < no->n_chaves; i++)
        adjacente->filmes[adjacente->n_chaves + i] = no->filmes[i];
    adjacente->n_chaves = adjacente->n_chaves + no->n_chaves;
    pai->end_filhos[posicao_no_pai] = -1;
    if(pai->n_chaves < index->ordem){
      TNo *novo_pai = le_no(index, pai->end_pai);
      TNo *temp;
      int posicao_no_pai_novo;
      for(posicao_no_pai_novo = 0; posicao_no_pai_novo < pai->n_chaves + 1; posicao_no_pai_novo++){
          if(pai->end_filhos[posicao_no_pai_novo] != -1){
              temp = le_no(index, pai->end_filhos[posicao_no_pai_novo]);
              if(temp == pai)
                  break;
          }
      }
      concatenacao(pai, le_no(index, pai->end_pai), le_no(index, pai->end_filhos[posicao_no_pai_novo]), posicao_no_pai_novo, pai->end_pai, index, end_filme, end_adjacente);
    }
    salva_no(no, index, end_filme);
    salva_no(adjacente, index, end_adjacente);
    salva_no(pai, index, end_pai);
}

//Caso de redistribuição da árvore
void redistribuicao(TNo *no_adjacente, TNo *pai, TNo *no, int posicao_no_pai, int end_pai, Index *index, int lado, int end_filme, int end_adjacente) {

    int i;
    //Se o lado do no_adjacente for direita, tenho que copiar primeiro os filmes do no, depois a raiz, depois o no_adjacente
    if(lado){
      no->filmes[no->n_chaves] = pai->filmes[posicao_no_pai];
      no->n_chaves++;
      no->filmes[posicao_no_pai] = no_adjacente->filmes[0];
      for(i=0; i<(no_adjacente->n_chaves)-1;i++){
        no_adjacente->filmes[i] = no_adjacente->filmes[i+1];
      }
      no_adjacente->filmes[no->n_chaves] = NULL;
      no_adjacente->n_chaves--;
    }else{ //se o lado do no_adjacente for esquerdo, tenho que copiar primeiro o no_adjacente, depois raiz, depois no
      for(i=no->n_chaves; i>0;i--){
        no->filmes[i] = no->filmes[i-1];
      }
      no->filmes[0] = pai->filmes[posicao_no_pai];
      no->n_chaves++;
      pai->filmes[posicao_no_pai] = no_adjacente->filmes[no_adjacente->n_chaves];
      no_adjacente->n_chaves--;
    }
    salva_no(no, index, end_filme);
    salva_no(no_adjacente, index, end_adjacente);
    salva_no(pai, index, end_pai);
}

int exclui(int ano, char *nome_filme, Index *index){
    FILE *arq = fopen(index->arvore, "wb");
    char *nome = cria_chave(nome_filme, ano);
    int *achou = 0;
    int end_filme = busca(nome, index, 0, achou);

    if(achou == 0){
        return -1;
    }else{
        TNo *no = le_no(index, end_filme);
        int i, indice_filme;
        for(i=0;i<no->n_chaves; i++){
          if(strcmp(nome, no->filmes[i]->titulo)==0){
            indice_filme = i;
          }
        }
        //É folha e vou apenas excluir, neste caso, só sobreescrever
        if(no->end_filhos[0] == -1){
          for(i = indice_filme; i < (no->n_chaves)-1; i++){
              no->filmes[i] = no->filmes[i+1];
          }
          no->filmes[(no->n_chaves)-1] = NULL;
          no->n_chaves--;
          //Casos especiais
          if(no->n_chaves < index->ordem){
              TNo *pai = le_no(index, no->end_pai);
              TNo *temp;
              int posicao_no_pai;
              for(posicao_no_pai = 0; posicao_no_pai < pai->n_chaves + 1; posicao_no_pai++){
                  if(pai->end_filhos[posicao_no_pai] != -1){
                      temp = le_no(index, pai->end_filhos[posicao_no_pai]);
                      if(temp == no)
                          break;

                  }
              }
              int end_adjacente, lado; //lado vai me dizer se o no_adjacente está na direita ou esquerda, 1 direita, 0 esquerda
              TNo *adjacente;
              if(posicao_no_pai == 0){
                  adjacente = le_no(index, pai->end_filhos[posicao_no_pai+1]);
                  lado = 1;
              }else{
                  adjacente = le_no(index, pai->end_filhos[posicao_no_pai-1]);
                  lado = 0;
              }
              if((adjacente->n_chaves + no->n_chaves) >= 2 * index->ordem){
                  redistribuicao(adjacente , pai, no, posicao_no_pai, no->end_pai, index, lado, end_filme, end_adjacente);}
              else{
                printf("Hello");
                  concatenacao(adjacente , pai, no, posicao_no_pai,no->end_pai,index,  end_filme, end_adjacente);
                }
          }
        }else{
          TNo *filho = le_no(index, no->end_filhos[indice_filme+1]);
          while(filho->end_filhos[0] != -1){
              filho = le_no(index, filho->end_filhos[0]);
          }
          no->filmes[indice_filme] = filho->filmes[0];
          int i;
          for(i = 0; i < (filho->n_chaves) - 1; i++)
              filho->filmes[i] = filho->filmes[i+1];
          filho->filmes[(filho->n_chaves) - 1] = NULL;
          filho->n_chaves--;
          if(filho->n_chaves < index->ordem){
            TNo *pai = le_no(index, no->end_pai);
            TNo *temp;
            int posicao_no_pai;
            for(posicao_no_pai = 0; posicao_no_pai < pai->n_chaves + 1; posicao_no_pai++){
                if(pai->end_filhos[posicao_no_pai] != -1){
                    temp = le_no(index, pai->end_filhos[posicao_no_pai]);
                    if(temp == no)
                        break;
                }
            }
            int end_adjacente, lado;
            TNo *adjacente;
            if(posicao_no_pai == 0){
                adjacente = le_no(index, pai->end_filhos[posicao_no_pai+1]);
                lado = 1;
            }else{
                adjacente = le_no(index, pai->end_filhos[posicao_no_pai-1]);
                lado = 0;
            }
            if((adjacente->n_chaves + no->n_chaves) >= 2 * index->ordem){
                redistribuicao(adjacente , pai, no, posicao_no_pai, no->end_pai, index, lado, end_filme, end_adjacente);}
            else{
                printf("Hello");
                concatenacao(adjacente , pai, no, posicao_no_pai,no->end_pai,index, end_filme, end_adjacente);
              }
          }
      }
      return end_filme;
    }
}

//Vai percorrer todo o arquivo buscando no por no pelo genero e excluindo
void remove_genero(char *genero, Index *index){
  FILE *arv = fopen(index->arvore, "rb");
  int i = 0;
  TNo *no_lido = le_no(index, i);
  while(no_lido != NULL){
    int j;
    for(j=0; j<no_lido->n_chaves;j++){
      if(strcmp(genero, no_lido->filmes[j]->genero)==0){
        exclui(no_lido->filmes[j]->ano, no_lido->filmes[j]->titulo, index);
      }
    }
    i++;
    no_lido = le_no(index, i*tamanho_no(index->ordem));
  }
  libera_no(no_lido, index->ordem);
  fclose(arv);
}
