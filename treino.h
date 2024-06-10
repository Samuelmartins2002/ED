typedef enum {
	HORTIFRUTI=1,
	PADARIA=2,
	LIMPEZA=3
}Setor;

typedef struct produto{
	char nome[50];
	int qtd;
	float preco;
	Setor setor;
}produto;

typedef struct nodolde{
	struct nodolde *ant;
	struct nodolde *prox;
	produto *info;
}nodolde;

typedef struct desclde{
	int tamanho;
	struct nodolde *inicio;
	struct nodolde *fim;
}desclde;

void setores();
void crialista(desclde *lista);
void inserirproduto(desclde *lista, char *nome, int qtd, float preco, Setor escolhido, int posicao);
void removerproduto(desclde *lista, int posicao);
void imprimirtodos(desclde *lista);
void consultarlista(desclde *lista, Setor escolhido);
