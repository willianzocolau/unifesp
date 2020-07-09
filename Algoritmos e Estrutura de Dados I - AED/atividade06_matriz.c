#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
//TAD.h
typedef struct Relacoes
{
	int m[MAX_N][MAX_N];
} TRelacoes;

typedef struct Celula
{
	int valor;
	struct Celula *proximo;
} TCelula;

typedef struct Lista
{
	struct Celula *inicio;
	struct Celula *fim;
	int qtd;
} TLista;

int n, d;
TRelacoes *matriz = NULL;

//TAD.c
TRelacoes* AlocarRelacoes();
TLista* AlocarLista();
TCelula* AlocarCelula();
void Inicializar();
void lerDados();
void Processar();
void Limpar();

TRelacoes* AlocarRelacoes()
{
	return (TRelacoes*)malloc(sizeof(TRelacoes));
}

TLista* AlocarLista()
{
	TLista *novo = (TLista*)malloc(sizeof(TLista));
	novo->qtd = 0;
	return novo;
}

TCelula* AlocarCelula()
{
	return (TCelula*)malloc(sizeof(TCelula));
}

void Inicializar()
{
	matriz = AlocarRelacoes();
}

void lerDados()
{
	int i, linha, coluna;
	for (i = 0; i < d; i++)
	{
		scanf("%d %d", &linha, &coluna);
		matriz->m[linha-1][coluna-1] = 1;
	}
}

void Processar()
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		int qtd_dependencias = 0, qtd_dependentes = 0;
		TLista *lista = AlocarLista();
		for (j = 0; j < n; j++)
		{
			if (matriz->m[i][j] == 1)//Dependentes
			{
				TCelula *novo = AlocarCelula();
				if (qtd_dependentes == 0){ lista->inicio = novo; lista->fim = novo; }
				else{ lista->fim->proximo = novo;lista->fim = novo;}
				novo->valor = j + 1;
				qtd_dependentes++;
				lista->qtd++;
			}

			if (matriz->m[j][i] == 1)//Dependencias
			{
				qtd_dependencias++;
			}
		}

		printf("%d %d %d", i + 1, qtd_dependencias, qtd_dependentes);
		TCelula *get = lista->inicio;
		TCelula *remover;
		for (j = 0; j < lista->qtd; j++)
		{
			printf(" %d", get->valor);
			remover = get;
			get = get->proximo;
			free(remover);
		}
		printf("\n");
		free(lista);
	}
}

void Limpar()
{
	free(matriz);
}

//Main
int main()
{
	Inicializar();
	scanf("%d %d", &n, &d);
	lerDados();
	Processar();
	return 0;
}
