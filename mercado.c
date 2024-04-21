// Lista 3
// 20/04/2024
// Samuel da Silva Martins (samuelmartins.aluno@unipampa.edu.br)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PADARIA = 1,
    ACOGUE,
    HORTIFRUTI,
    LIMPEZA,
    BEBIDAS,
    ENLATADOS,
    CEREAIS,
    OUTROS
} setores;

typedef struct {
    char nome_produto[16];
    setores setor_mercado;
    int qtd;
    float preco_por_unidade;
} produto;

void inserir_prod(FILE *arquivo, produto *prods, int qtd_cadastrados);
setores escolher_setor();
void apresenta_um_produto(produto *prods, int qtd_cadastrados);
void apresenta_todos(produto *prods);
int busca_nome(produto *prods);
int busca_setor(FILE *arquivo, produto *prods);
float balanco(produto *prods, int qtd_cadastrados);
int venda(FILE *arquivo, produto *prods);

int main(){
    int qtd_cadastrados;
    int escolha;
    FILE *arquivo;

    arquivo = fopen("mercado.txt", "a+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    printf("Informe quantos produtos serão cadastrados: ");
    scanf("%d", &qtd_cadastrados);

    produto *prods = (produto *)malloc(qtd_cadastrados * sizeof(produto));

    do {
        printf("=========MENU==========\n");
        printf("1) Inserir produto\n");
        printf("2) Apresentar 1 Produto\n");
        printf("3) Apresentar todos os produtos\n");
        printf("4) Apresentar balanço\n");
        printf("5) Buscar produto por nome\n");
        printf("6) Buscar produtos por setor\n");
        printf("7) Vender produto\n");
        printf("0) Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 0:
                printf("Programa Encerrado!!!\n");
                break;
            case 1:
                inserir_prod(arquivo, prods, qtd_cadastrados);
                setbuf(stdin, NULL);
                break;
            case 2:
                /*apresenta_um_produto(prods, qtd_cadastrados);*/
                break;
            case 3:
                apresenta_todos(prods);
                break;
            case 4:
                printf("Balanço total: R$%.2f\n", balanco(prods, qtd_cadastrados));
                break;
            case 5:
                busca_nome(prods);
                break;
            case 6:
                busca_setor(fopen("mercado.txt", "r"), prods);
                break;
          case 7: 
                venda(arquivo, prods);
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (escolha != 0);
    fclose(arquivo);
    free(prods);
}

void inserir_prod(FILE *arquivo, produto *prods, int qtd_cadastrados) {

    printf("Digite o nome do produto: \n");
    scanf(" %15[^\n]", prods->nome_produto);
    prods->setor_mercado = escolher_setor();
    printf("Digite a quantidade desse produto: \n");
    scanf("%d", &prods->qtd);
    printf("Digite o preço por unidade do produto R$: \n");
    scanf("%f", &prods->preco_por_unidade);

    fprintf(arquivo, "Produto: %s \nSetor: %d \nQuantidade: %d \nPreço: R$%.2f\n =======================================\n", prods->nome_produto, prods->setor_mercado, prods->qtd, prods->preco_por_unidade);

}

setores escolher_setor(){
    int setor_prod;
    printf("Qual é o setor do produto? 1-Padaria\n 2-Açogue\n 3-Hortifruti\n 4-Limpeza\n 5-Bebidas\n 6-Enlatados\n 7-Cereais\n  8-Outros\n");
    scanf("%d", &setor_prod);
    while (setor_prod < PADARIA || setor_prod > OUTROS) {
        printf("Escolha inválida. Por favor, tente novamente: ");
        scanf("%d", &setor_prod);
    }
    return (setores)setor_prod;
}

/*void apresenta_um_produto(produto *prods, int qtd_cadastrados){

} */

void apresenta_todos(produto *prods) {
    produto temp_produto;
    FILE *arquivo = fopen("mercado.txt", "r");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo.\n");
    }
    while(fscanf(arquivo, "Produto: %15[^\n] \nSetor: %d \nQuantidade: %d \nPreço: R$%f\n =======================================\n",
   temp_produto.nome_produto, &temp_produto.setor_mercado,
   &temp_produto.qtd, &temp_produto.preco_por_unidade) != EOF) {
      printf("Produto: %s\n", temp_produto.nome_produto);
      printf("Setor: %d\n", temp_produto.setor_mercado);
      printf("Quantidade: %d\n", temp_produto.qtd);
      printf("Preço por unidade: R$%.2f\n", temp_produto.preco_por_unidade);
      printf("=======================================\n");
  }
  fclose(arquivo);
}

float balanco(produto *prods, int qtd_cadastrados) {
    float total = 0.0;
    produto temp_produto;
    FILE *arquivo = fopen("mercado.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    while (fscanf(arquivo, "Produto: %15[^\n] \nSetor: %d \nQuantidade: %d \nPreço: R$%f\n =======================================\n",
                 temp_produto.nome_produto, &temp_produto.setor_mercado,
                 &temp_produto.qtd, &temp_produto.preco_por_unidade) != EOF) {
        total += temp_produto.qtd * temp_produto.preco_por_unidade;
    }

    fclose(arquivo);

    return total;
}

int busca_nome(produto *prods){
    char nome_prod[16];
    int encontrado = 0;
    produto temp_produto;
    FILE *arquivo = fopen("mercado.txt", "r");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo.\n");
    }

    printf("Digite o nome do produto: ");
    scanf(" %15[^\n]", nome_prod);

    //problema na leitura do nome do produto com fscanf, pois quando utilizo %15[^\n] ele lê apenas produtos que tenham 15 caracteres (conttando com espaçamento).
    while(fscanf(arquivo, "Produto: %15[^\n] \nSetor: %d \nQuantidade: %d \nPreço: R$%f\n =======================================\n",
   temp_produto.nome_produto, &temp_produto.setor_mercado,
   &temp_produto.qtd, &temp_produto.preco_por_unidade) != EOF) {
    if(strcmp(nome_prod, temp_produto.nome_produto) == 0){
      encontrado = 1;
      printf("Produto: %s\n", temp_produto.nome_produto);
      printf("Setor: %d\n", temp_produto.setor_mercado);
      printf("Quantidade: %d\n", temp_produto.qtd);
      printf("Preço por unidade: R$%.2f\n", temp_produto.preco_por_unidade);
      break;
    }
  }
    if(!encontrado){
        printf("Produto não encontrado");
    }

  fclose(arquivo);

  return encontrado;
}

int busca_setor(FILE *arquivo, produto *prods){
  int setor;
  int encontrado = 0;
  produto temp_produto;

  printf("Digite o setor que deseja encontrar: ");
  scanf("%d", &setor);

  rewind(arquivo);

  while (fscanf(arquivo, "Produto: %15[^\n] \nSetor: %d \nQuantidade: %d \nPreço: R$%f\n =======================================\n",
               temp_produto.nome_produto, &temp_produto.setor_mercado,
               &temp_produto.qtd, &temp_produto.preco_por_unidade) != EOF) {
      if (temp_produto.setor_mercado == setor) {
          encontrado = 1;
          printf("Produto: %s\n", temp_produto.nome_produto);
          printf("Setor: %d\n", temp_produto.setor_mercado);
          printf("Quantidade: %d\n", temp_produto.qtd);
          printf("Preço por unidade: R$%.2f\n", temp_produto.preco_por_unidade);
          printf("=======================================\n");
      }
  }
      if(!encontrado){
          printf("Produto não encontrado");
      }

  return encontrado; 
}

int venda(FILE *arquivo, produto *prods) {
    char nome_venda[16];
    int qtd_venda;
    produto temp_produto;
    int encontrado = 0;

    printf("Digite o nome do produto que deseja vender: ");
    scanf(" %15[^\n]", nome_venda);

    rewind(arquivo);

    FILE *temp_arquivo = fopen("temp.txt", "w");
    if (temp_arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        return 0;
    }

    while (fscanf(arquivo, "Produto: %15[^\n] \nSetor: %d \nQuantidade: %d \nPreço: R$%f\n =======================================\n",
              temp_produto.nome_produto, &temp_produto.setor_mercado,
              &temp_produto.qtd, &temp_produto.preco_por_unidade) != EOF) {
        if (strcmp(nome_venda, temp_produto.nome_produto) == 0) {
            encontrado = 1;

            printf("Produto: %s\n", temp_produto.nome_produto);
            printf("Setor: %d\n", temp_produto.setor_mercado);
            printf("Quantidade disponível: %d\n", temp_produto.qtd);
            printf("Preço por unidade: R$%.2f\n", temp_produto.preco_por_unidade);

            printf("Digite a quantidade que deseja vender: ");
            scanf("%d", &qtd_venda);

            if (qtd_venda > temp_produto.qtd) {
                printf("Quantidade indisponível para venda.\n");
            } else {
                temp_produto.qtd -= qtd_venda;
                printf("Venda realizada com sucesso.\n");
            }
        }

        fprintf(temp_arquivo, "Produto: %s \nSetor: %d \nQuantidade: %d \nPreço: R$%.2f\n =======================================\n",
                temp_produto.nome_produto, temp_produto.setor_mercado, temp_produto.qtd, temp_produto.preco_por_unidade);
    }
    fclose(arquivo);
    fclose(temp_arquivo);

    remove("mercado.txt");

    rename("temp.txt", "mercado.txt");

    if (!encontrado) {
        printf("Produto não encontrado\n");
    }

    return encontrado;
}
