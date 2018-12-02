#include <string.h>
#include <stdlib.h>

#include "index.h"

Index *index(FILE* arvore) {
    Index *index = (Index *) malloc(sizeof(Index));
    index->qtd_filmes = 0;
    index->prox_pos_livre = 0;
    index->arvore = arvore;
    return index;
}

// TO-DO
// Le o arquivo de dados e imprime a biblioteca
void *le_biblioteca() {
}
