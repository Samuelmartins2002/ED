#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treino.h"

int main(){
	desclde *lista = (desclde*)malloc(sizeof(desclde));
	int opcao, listacriada=0;
	char nome[50];
	int qtd, posicao, posicao_procurada;
	float preco;
	do{
		printf("----MENU----\n");
		printf("1 - Criar Lista\n");
		printf("2 - Inserir\n");
		printf("3 - Remover\n");
                printf("4 - Consultar\n");
		printf("5 - Imprimir\n");
		printf("6 - Sair\n");
		scanf("%d", &opcao);
		getchar();

		switch (opcao){
			case 1:
				crialista(lista);
				listacriada=1;
				printf("Lista criada com sucesso!!\n");
				break;
			case 2:
				printf("Digite o nome do alimento: ");
				fgets(nome, 50, stdin);
				nome[strcspn(nome, "\n")] = '\0';

				printf("Digite a quantidade de produtos que deseja: ");
				scanf("%d", &qtd);
				getchar();

				printf("Digite o preço por unidade: R$");
				scanf("%f", &preco);
				getchar();

				int setor_escolhido;
				setores();
				scanf("%d", &setor_escolhido);
				Setor escolhido = (Setor)setor_escolhido;

				printf("Digite a posição que deseja inserir na lista: \n");
				scanf("%d", &posicao);
				getchar();

				inserirproduto(lista, nome, qtd, preco, escolhido, posicao);
				break;
			case 3:
				printf("Digite a posição que deseja remover da lista: \n");
                                scanf("%d", &posicao_procurada);
                                getchar();

				removerproduto(lista, posicao_procurada);
				break;
			case 4:
				setores();
				printf("Escolha o setor que deseja consultar na lista: \n");
                                scanf("%d", &setor_escolhido);
				Setor esc = (Setor)setor_escolhido;
                                getchar();

				consultarlista(lista, esc);
				break;
			case 5:
				imprimirtodos(lista);
				break;
			case 6:
				printf("Saindo...\n");
				break;
			default:
				printf("Opção inválida\n");
				break;
		}
	} while(opcao!=6);
	return 0;
}
