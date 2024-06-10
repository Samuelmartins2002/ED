typedef enum {
	COMPUTACAO=1, 
	MATEMATICA=2, 
	PRODUCAO=3
} curso;

typedef struct aluno {
	char nome[50];
	int matricula;
	float media_geral;
	curso escolhido;
} aluno;

typedef struct desclde {
	struct nodolde *inicio;
	struct nodolde *fim;
	int tamanho;
} desclde;

typedef struct nodolde {
	struct nodolde *prox;
	struct nodolde *ant;
	aluno *info;
} nodolde;

void opcoescurso();
void crialista(desclde *lista);
void inseriraluno(desclde *lista, char *nome, int matricula, float media, int posicao, curso escolhido);
void removeraluno(desclde *lista, int posicao);
void consultacurso(desclde *lista, curso escolhido);
const char* nome_curso(curso curso);
float media_mais_alta(nodolde *atual, float maior_media);
void mostrar_maior(desclde *lista);
