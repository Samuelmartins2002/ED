#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treino.h"

void setores(){
	printf("Escolha o setor\n");
	printf("1 - Hortifruti\n");
	printf("2 - Padaria\n");
	printf("3 - Limpeza\n");
}

void crialista(desclde *lista){
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->tamanho = 0;
}

void inserirproduto(desclde *lista, char *nome, int qtd, float preco, Setor escolhido, int posicao){
	if(posicao < 1){
		printf("Posicao inválida!!!\n");
	}
	produto *novoproduto = (produto*)malloc(sizeof(produto));
	strcpy(novoproduto->nome, nome);
	novoproduto->qtd = qtd;
	novoproduto->preco = preco;
	novoproduto->setor = escolhido;

	nodolde *novonodo = (nodolde*)malloc(sizeof(nodolde));
	novonodo->info = novoproduto;
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
		int i=0;
		while(i < posicao && atual != NULL){
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
		} else if(i == lista->tamanho){
			lista->fim->prox = novonodo;
			novonodo->ant = lista->fim;
			lista->fim = novonodo;
		} else {
			printf("Posição inválida");
			free(novoproduto);
			free(novonodo);
		}
	}
	lista->tamanho++;
}

void removerproduto(desclde *lista, int posicao){
	if(posicao < 1){
		printf("Posição inválida");
	}
	nodolde *aux = lista->inicio;
	nodolde *ant = NULL;
	if(posicao == 1){
		lista->inicio = aux->prox;
		free(aux->info);
		free(aux);
		lista->tamanho--;
	} else {
		for(int i=0; i < posicao && aux != NULL; i++){
			ant = aux;
			aux = aux->prox;
		}
		if(aux == NULL){
			printf("Posição inexistente\n");
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

void consultarlista(desclde *lista, Setor escolhido){
	nodolde *atual = lista->inicio;
	while(atual != NULL){
		if(atual->info->setor == escolhido){
			printf("Nome: %s\n", atual->info->nome);
			printf("Quantidade: %d\n", atual->info->qtd);
			printf("Preço: %f\n", atual->info->preco);
                        printf("Setor: %d", atual->info->setor);
		}
		atual = atual->prox;
	}
}

void imprimirtodos(desclde *lista){
	nodolde *atual = lista->inicio;
	while(atual != NULL){
		produto *info = atual->info;
		printf("Nome: %s\n Quantidade: %d\n Preço: %.2f\n Setor: %d\n", info->nome, info->qtd, info->preco, info->setor);
		atual = atual->prox;
	}
}
