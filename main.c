#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arvore.h"
#include "index.h"

Index *monta_biblioteca(char *arq_nome, char *arq_index, int o) {
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
return index;
}

// Aqui roda a parte "UI" do programa, que interage com o usuário
void execucao(Index *index) {
  int opcao;
  printf("O que desejas fazer? \n");
  printf("(1) Inserir Filme) \n");
  printf("(2) Remover Filme \n");
  printf("(3) Buscar Filme\n");
  printf("(4) Aletrar Info  \n");
  printf("(5) Buscar Filmes de um Diretor  \n");
  printf("(6) Remover Filmes por Genero  \n");
  scanf("%i", &opcao);
  char filme[80];
  char Diretor[50];
  char genero[30];
  int ano;
  switch(opcao){
    case 1:
      printf("Tem que por o que vai fazer na inserção");
    case 2:
      printf("Remocao \n");
      printf("Digite o ano e o nome do filme \n Filme: \n Ano:" );
      scanf("%i\n", &ano);
      scanf("%[^\n]s ",filme);
      exclui(ano, filme, index);
    case 3:
      printf("Busca \n");
      printf("Digite o nome filme e o ano \n Filme: \n Ano: ");
      char chave[86];
      scanf("%[^\n]s ",filme);
      scanf("%i\n", &ano);
      strcpy(chave,cria_chave(filme, ano));
      busca(chave, index, 0, 0);
    case 4:
      printf("Alteracao \n");
      printf("Digite o nome do filme e o ano \n Filme: \n Ano: ");
      scanf("%[^\n]s ",filme);
      scanf("%i\n", &ano);
      altera(filme, ano, index);
    case 5:
      printf("Digite o diretor: ");
      scanf("%[^\n]s ",Diretor);
      busca_por_diretor(Diretor, index);
    case 6:
      printf("Digite o genero: ");
      scanf("%[^\n]s ",genero);
      remove_genero(genero, index);
  }
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
  Index *falha = monta_biblioteca(arq_dados, arq_arv, ordem);
  //if(falha != 0) exit(-1);

  // Rodo a interface de usuário para interagir com a biblioteca
  execucao(falha);
  return 0;
}
