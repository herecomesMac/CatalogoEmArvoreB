#include <stdlib.h>

#include "no.h"

void imprime_no(No *no) {
    int i;
    printf("%d, %d, (", no->m, no->pont_pai);
    for (i = 0; i < 2 * D; i++) {
        printf("%d, ", no->p[i]);
    }
    printf("%d), (\n", no->p[i]);
    for (i = 0; i < 2 * D; i++) {
        printf("  ");
        if (no->filmes[i])
            imprime_filme(no->filmes[i]);
    }
    printf(")\n");
}

No *no_vazio(){
    int i;
    No *no = (No *) malloc(sizeof(No));
    no->m = 0;
    no->pont_pai = -1;
    no->p = (int *) malloc(sizeof(int) * (2 * D + 1));
    no->filmes = (Filme **) malloc(sizeof(Filme *) * 2 * D);
    for (i = 0; i < 2 * D; i++) {
        no->p[i] = -1;
        no->filmes[i] = NULL;
    }
    no->p[2 * D] = -1;
    return no;
}

void salva_no(No *no, FILE *out) {
    int i;
    fwrite(&no->m, sizeof(int), 1, out);
    fwrite(&no->pont_pai, sizeof(int), 1, out);
    //garantidamente, sempre havera pelo menos 1 chave no noh
    //portanto, p0 sempre vai existir
    fwrite(&no->p[0], sizeof(int), 1, out);

    Filme *vazio = filme("", -1, "", "", -1);

    for (i = 0; i < 2 * D; i++) {
        if (no->filmes[i]) {
            salva_filme(no->filmes[i], out);
        } else {
            salva_filme(vazio, out);
        }
        fwrite(&no->p[i + 1], sizeof(int), 1, out);
    }
    free(vazio);
}

No *le_no(FILE *in) {
    int i;
    No *no = (No *) malloc(sizeof(No));
    if (0 >= fread(&no->m, sizeof(int), 1, in)) {
        free(no);
        return NULL;
    }
    fread(&no->pont_pai, sizeof(int), 1, in);
    no->p = (int *) malloc(sizeof(int) * (2 * D + 1));
    no->filmes = (Filme **) malloc(sizeof(Filme *) * 2 * D);

    fread(&no->p[0], sizeof(int), 1, in);
    for (i = 0; i < no->m; i++) {
        no->filmes[i] = le_filme(in);
        fread(&no->p[i + 1], sizeof(int), 1, in);
    }

    // Termina de ler dados nulos para resolver problema do cursor
    // Dados lidos sao descartados
    Filme *vazio;
    int nul = -1;
    for (i = no->m; i < 2 * D; i++) {
        no->filmes[i] = NULL;
        vazio = le_filme(in);
        fread(&no->p[i + 1], sizeof(int), 1, in);
        free(vazio);
    }
    return no;
}

void libera_no(No *no) {
    int i;
    for (i = 0; i < 2 * D; i++) {
        free(no->filmes[i]);
    }
    free(no->filmes);
    free(no->p);
    no->filmes = NULL;
    no->p = NULL;
    free(no);
}

int tamanho_no(){
    return sizeof(int) +
           sizeof(int) +
           sizeof(int) * (2 * D + 1) +
           tamanho_filme() * (2 * D);
}