#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arvore.h"

int monta_biblioteca(char *arq_nome, char *arq_index, int o) {
  printf("Lendo arquivo... \n");

  //Abre o arquivo e trata caso dê erro
  FILE *arq = fopen(arq_nome, "r");
  if(!arq){
    printf("Nao foi possível abrir o arquivo!\n");
    exit(1);
  }
  printf("Arquivo lido!\n");

  // Abrindo arquivos, criando o objeto do index e o buffer
  printf("Gerando a biblioteca...\n");
  Index *index = cria_index(arq_index, o);
  size_t buffer_size = sizeof(TMovie);
  char* buffer = (char *)malloc(buffer_size);

  if(buffer == NULL || !index) {
    printf("Sem espaço na memória :(\n");
    exit(1);
  }

  // leio cada linha, crio um filme e insiro na árvore
  size_t tam_linha;
   while ((tam_linha = getline(&buffer, &buffer_size, arq)) != -1) {
    TMovie *novo = cria_da_linha(buffer);
    int falhou = insere_filme(index, novo);
    if(falhou != 0) {
      printf("Houve uma falha na inserção do filme %s\n", novo->titulo);
    }
   }
  printf("Tudo pronto! Sua biblioteca tem %d titulos no momento.\n", index->qtd_filmes);
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
  char *arq_dados = (char*)malloc(sizeof(char)*260); // tamanho do caminho no Windows
  char *arq_arv = (char*)malloc(sizeof(char)*260); // tamanho do caminho no Windows
  printf("Insira a ordem da árvore: ");
  scanf("%i", &ordem);

  printf("Insira o caminho para o arquivo de dados iniciais: ");
  scanf("%s", arq_dados);

  printf("Insira o caminho para o arquivo da árvore: ");
  scanf("%s", arq_arv);

  // monto a árvore inicial com os dados e retorno 0 se teve sucesso
  int falha = monta_biblioteca(arq_dados, arq_arv, ordem);
  if(falha != 0) exit(-1);

  // Rodo a interface de usuário para interagir com a biblioteca
  // execucao();
  return 0;
}
