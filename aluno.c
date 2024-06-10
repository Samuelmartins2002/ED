#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aluno.h"

const char* nome_curso(curso curso){
	switch(curso){
		case COMPUTACAO:
			return "Computação";
		case MATEMATICA:
			return "Matemática";
		case PRODUCAO:
			return "Produção";
		default:
			return "Desconhecido";
	}
}

void opcoescurso(){
	printf("--Escolha seu curso--\n");
	printf("1 - Computação\n");
	printf("2 - Matemática\n");
	printf("3 - Produção\n");
}

void crialista(desclde *lista){
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->tamanho = 0;
}

void inseriraluno(desclde *lista, char *nome, int matricula, float media_geral, int posicao, curso escolhido){
	if(posicao < 1){
		printf("Posição inexistente");
		return;
	}
	aluno *novoaluno = (aluno*)malloc(sizeof(aluno));
	strcpy(novoaluno->nome, nome);
	novoaluno->matricula = matricula;
	novoaluno->media_geral = media_geral;
	novoaluno->escolhido = escolhido;

	nodolde *novonodo = (nodolde*)malloc(sizeof(nodolde));
	novonodo->info = novoaluno; 
	novonodo->prox = NULL;
	novonodo->ant = NULL;

	if(posicao == 1){
		if(lista->inicio == NULL){
			lista->inicio = novonodo;
			lista->fim = novonodo;
		} else {
			novonodo->prox = lista->inicio;
			lista->inicio->ant = novonodo;
			lista->inicio = novonodo;
		}
	} else {
		nodolde *atual = lista->inicio;
		int i = 0;
		while(i < posicao - 1 && atual != NULL){
			atual = atual->prox;
			i++;
		}
		if(atual != NULL){
			novonodo->prox = atual->prox;
			if(atual->prox != NULL){
				atual->prox->ant = novonodo;
			} else {
				lista->fim = novonodo;
			}
			novonodo->ant = atual;
			atual->prox = novonodo;
		} else if(i == lista->tamanho){
			lista->fim->prox = novonodo;
			novonodo->ant = lista->fim;
			lista->fim = novonodo;
		} else {
			printf("Posição inválida!!!");
			free(novoaluno);
			free(novonodo);
			return;
		}
	}
	lista->tamanho++;
}

void removeraluno(desclde *lista, int posicao){
	if(posicao < 1){
                printf("Posição inexistente");
                return;
        }
	nodolde *aux = lista->inicio;
	nodolde *ant = NULL;

	if(posicao == 1){
		lista->inicio = aux->prox;
		free(aux->info);
		free(aux);
		lista->tamanho--;
		return;
	} else {
		for(int i=0; i < posicao && aux != NULL; i++){
			ant = aux;
			aux = aux->prox;
		}
		if(aux == NULL){
			printf("Posição inexistente");
			return;
		}
		ant->prox = aux->prox;
		if(aux == lista->fim){
			lista->fim = ant;
		}
		free(aux->info);
		free(aux);
		lista->tamanho--;
	}
}

void consultacurso(desclde *lista, curso escolhido){
	nodolde *atual = lista->inicio;

	while(atual != NULL){
		if(atual->info->escolhido == escolhido){
			printf("Nome: %s\n", atual->info->nome);
			printf("Matrícula: %d\n", atual->info->matricula);
			printf("Média geral: %.2f\n", atual->info->media_geral);
			printf("Curso: %d\n", atual->info->escolhido);
		}
	atual = atual->prox;
	}
}

float media_mais_alta(nodolde *atual, float maior_media){
	if(atual == NULL){
		return maior_media;
	}

	if(atual->info->media_geral > maior_media){
		maior_media = atual->info->media_geral;
	}

	return media_mais_alta(atual->prox, maior_media);
}

void mostrar_maior(desclde *lista){
	if(lista->inicio == NULL){
		printf("A lista está vazia!!\n");
		return;
	}
	float maior_media = 0.0;
	maior_media = media_mais_alta(lista->inicio, maior_media);
	printf("A maior média é: %.2f", maior_media);
}
