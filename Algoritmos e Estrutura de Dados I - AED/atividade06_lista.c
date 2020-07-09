#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TAD.h
typedef struct Celula
{
	int valor;
	struct Celula *proximo;
} TCelula;

typedef struct Relacoes
{
	int qtd_dependencias;
	int qtd_dependentes;
	struct Celula *inicio;
	struct Celula *fim;
} TRelacoes;

int n, d;
TRelacoes *lista = NULL;

//TAD.c
TRelacoes* AlocarRelacoes();
TCelula* AlocarCelula();
void Inicializar();
void lerDados();
void Processar();
void Limpar();

TRelacoes* AlocarRelacoes()
{
	return (TRelacoes*)malloc(sizeof(TRelacoes) * 100);
}

TCelula* AlocarCelula()
{
	return (TCelula*)malloc(sizeof(TCelula));
}

void Inicializar()
{
	lista = AlocarRelacoes();
}

void lerDados()
{
	int i, linha, coluna;
	for ( i = 0; i < n; i++)
	{
		lista[i].qtd_dependencias = 0;
		lista[i].qtd_dependentes = 0;
	}

	for (i = 0; i < d; i++)
	{
		scanf("%d %d", &linha, &coluna);
		TCelula  *nova = AlocarCelula();
		nova->valor = coluna;
		if (lista[(linha - 1)].qtd_dependentes == 0)
		{
			lista[(linha - 1)].inicio = nova;
			lista[(linha - 1)].fim = nova;
		}
		else
		{
			lista[(linha - 1)].fim->proximo = nova;
			lista[(linha - 1)].fim = nova;
		}
		lista[(linha - 1)].qtd_dependentes++;
		lista[(coluna - 1)].qtd_dependencias++;
	}
}

void Processar()
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		printf("%d %d %d", i + 1, lista[i].qtd_dependencias, lista[i].qtd_dependentes);
		TCelula *get = lista[i].inicio;
		TCelula *remover;
		for (j = 0; j < lista[i].qtd_dependentes; j++)
		{
			printf(" %d", get->valor);
			remover = get;
			get = get->proximo;
			free(remover);
		}
		printf("\n");
	}
}

void Limpar()
{
	free(lista);
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
