#ifndef NO_H
#define NO_H

#include "filme.h"

#define D 6

typedef struct No {
    int m;
    int pont_pai;
    int *p;
    Filme **filmes;
} No;

void imprime_no(No *no);

No *no(int m, int pont_pai);

No *no_vazio();

No *cria_no(int m, int pont_pai, int size, ...);

void salva_no(No *no, FILE *out);

No *le_no(FILE *in);

int tamanho_no();

void libera_no(No *no);

#endif
