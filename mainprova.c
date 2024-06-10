#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

int main(){
	desclde *lista = (desclde*)malloc(sizeof(desclde));
	int opcao, listacriada = 0, matricula, posicao, posicaoprocurada;
	char nome[50];
	int curso_escolhido;
	float media;
	do{
		printf("----MENU----\n");
		printf("1 - Criar Lista\n");
		printf("2 - Inserir aluno\n");
		printf("3 - Remover aluno\n");
		printf("4 - Maior média geral\n");
                printf("5 - Imprimir por curso\n");
                printf("6 - Sair\n");
		scanf("%d", &opcao);
		getchar();

		switch (opcao){
			case 1:
				crialista(lista);
				printf("Lista criada com sucesso!!!\n");
				listacriada = 1;
				break;
			case 2:
				if(!listacriada){
                                        printf("Necessário criar uma lista antes\n");
                                	break;
				}
				printf("Digite o nome do aluno: ");
				fgets(nome, 50, stdin);
				nome[strcspn(nome, "\n")] = '\0';

				printf("Digite a matrícula do aluno: ");
				scanf("%d", &matricula);
				getchar();

				printf("Digite a posição que o aluno será inserido na lista: ");
				scanf("%d", &posicao);
				getchar();

				printf("Digite a média do aluno: ");
				scanf("%f", &media);
				getchar();

				opcoescurso();
				scanf("%d", &curso_escolhido);
				curso escolhido = (curso)curso_escolhido;

				inseriraluno(lista, nome, matricula, media, posicao, escolhido);
				break;
			case 3:
				if(!listacriada){
					printf("Necessário criar uma lista antes\n");
					break;
				}
				printf("Digite a posição do aluno que deseja excluir: ");
				scanf("%d", &posicaoprocurada);
				getchar();

				removeraluno(lista, posicaoprocurada);
				break;
			case 4:
				if(!listacriada){
                                        printf("Necessário criar uma lista antes\n");
                                        break;
                                }

				mostrar_maior(lista);
				break;
			case 5:
				if(!listacriada){
                                        printf("Necessário criar uma lista antes\n");
                                        break;
                                }
				opcoescurso();
				scanf("%d", &curso_escolhido);
				curso escolhid = (curso)curso_escolhido;
				consultacurso(lista, escolhid);
				break;
			case 6:
				printf("Saindo...");
				break;
			default:
				printf("Opção inválida");
				break;
		}
	}while(opcao!=6);
	return 0;
}
