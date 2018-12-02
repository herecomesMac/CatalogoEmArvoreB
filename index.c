#include <string.h>
#include <stdlib.h>

#include "index.h"

Index *cria_index(char* nome_arq_arv, int ordem) {
    Index *index = (Index *) malloc(sizeof(Index));
    index->qtd_filmes = 0;
    index->prox_pos_livre = 0;
    index->ordem = ordem;
    index->arvore = nome_arq_arv;
    return index;
}

// TO-DO
// Le o arquivo de dados e imprime a biblioteca
void *le_biblioteca(Index *index) {
  printf("%s\n", index->arvore);
}
