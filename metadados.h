#ifndef METADADOS_H
#define METADADOS_H

#include <stdio.h>

typedef struct Metadados {
    int pont_raiz;
    int pont_prox_no_livre;
} Metadados;

void imprime_metadados(Metadados *metadados);

Metadados *metadados(int pont_raiz, int pont_prox_no_livre);

void salva_metadados(Metadados *metadados, FILE *out);

void salva_arq_metadados(char *nome_arquivo, Metadados *metadados);

Metadados *le_metadados(FILE *in);

Metadados *le_arq_metadados(char *nome_arquivo);

int cmp_metadados(Metadados *c1, Metadados *c2);

int tamanho_metadados();

#endif
