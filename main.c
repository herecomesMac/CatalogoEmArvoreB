#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arvore.h"

int monta_biblioteca(char *arq_nome, int o) {
  printf("Lendo arquivo... \n");

  //Abre o arquivo e trata caso dê erro
  FILE *arq = fopen(arq_nome, "r");
  if(!arq){
    printf("Nao foi possível abrir o arquivo!\n");
    exit(1);
  }
  printf("Arquivo lido!\n");

  //Lê o arquivo linha a linha
  printf("Gerando a biblioteca...\n");
  FILE *index = fopen("index.txt", "wb");
  size_t buffer_size = sizeof(TMovie);
  char* buffer = (char *)malloc(buffer_size);
  if(buffer == NULL || index == NULL) {
    printf("Sem espaço na memória :(\n");
    exit(1);
  } //declarando o tamanho da linha separado porque deu ruim
  size_t tam_linha;
  TNo *arv = cria_no(o);

  // para cada linha, crio um filme e insiro na árvore
  while ((tam_linha = getline(&buffer, &buffer_size, arq)) != -1) {
    TMovie *novo = cria_da_linha(buffer);
    //insere_no(arv, novo, o);
  }
  printf("Tudo pronto! Sua biblioteca tem AQUI titulos no momento.\n");
  fclose(arq);
return 0;
}

// Aqui roda a parte "UI" do programa, que interage com o usuário
void execucao() {
  printf("Hello, I'm working! \n");
  return;
}

int main(){
  // pegando os dados iniciais
  int ordem;
  char *arq_dados;
  printf("Insira a ordem da árvore: ");
  scanf("%i", &ordem);
  // printf("Insira o nome do arquivo de dados: ");
  // scanf("%s", arq_dados);

  // monto a árvore inicial com os dados e retorno 0 se teve sucesso
  int falha = monta_biblioteca("filmes.txt", ordem);
  if(falha != 0) exit(-1);

  // Rodo a interface de usuário para interagir com a biblioteca
  // execucao();
  return 0;
}
