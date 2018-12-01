#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arvore.h"

TNo *monta_biblioteca(char *nomedoarquivo,int d) {
  printf("Lendo arquivo... \n");

  //Abre o arquivo e trata caso dê erro
  FILE *arq = fopen(nomedoarquivo, "r");
  if(!arq){
    printf("Nao foi possível abrir o arquivo!\n");
    exit(1);
  }
  printf("Arquivo lido!\n");

  //Lê o arquivo linha a linha
  printf("Gerando a biblioteca...\n");
  size_t buffer_size = sizeof(TMovie);
  char* buffer = (char *)malloc(buffer_size);
  if(buffer == NULL) {
    printf("Sem espaço na memória :(\n");
    exit(1);
  } //declarando o tamanho da linha separado porque deu ruim
  size_t tam_linha;
  int count = 0;
  TNo *arv = inicializa_no(d);

  // para cada linha, crio um nó e insiro na árvore
  while ((tam_linha = getline(&buffer, &buffer_size, arq)) != -1) {
    TNo *novo = cria_da_linha(buffer);
    insere_no(arv, novo);
    count++;
  }
  printf("Tudo pronto! Sua biblioteca tem %d titulos no momento.\n", count);
  fclose(arq);
return arv;
}

// Aqui roda a parte "UI" do programa, que interage com o usuário
void execucao() {
  printf("Hello, I'm working! \n");
  return;
}


int main(){
  int d;
  printf("Entre coma ordem da arvore: ");
  scanf("%i", &d);
  TNo *raiz = inicializa_no(d);
  raiz = monta_biblioteca("filmes.txt", d);
  execucao();
  return 0;
}
