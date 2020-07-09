#include <stdio.h>
#include <stdlib.h>

#define MAX_N 7
//TAD.h
typedef struct Relacoes
{
	int grau[MAX_N];
} TRelacoes;

int n;
TRelacoes *relacoes = NULL;

TRelacoes* AlocarRelacoes();
void Inicializar();
void lerDados();
void Processar();
void Limpar();

//TAD.c
TRelacoes* AlocarRelacoes()
{
	return (TRelacoes*)malloc(sizeof(TRelacoes));
}

void Inicializar()
{
	relacoes = AlocarRelacoes();
	int i;
	for (i = 0; i < 7; i++)
	{
		relacoes->grau[i] = 0;
	}
}

void lerDados()
{
	int i, linha, coluna;
	for (i = 0; i < n; i++)
	{
		scanf("%d %d", &linha, &coluna);
		relacoes->grau[linha]++;
		relacoes->grau[coluna]++;
	}
}

void Processar()
{
	int qtd_pecas_impar = 0, i;
	for (i = 0; i < 7; i++)
	{
		if ((relacoes->grau[i] % 2) == 1)
		{
			qtd_pecas_impar++;
		}
	}

	if (qtd_pecas_impar > 2)
	{
		printf("0");
	}
	else
	{
		printf("1");
	}
}

void Limpar()
{
	free(relacoes);
}

//Main.c
int main()
{
	Inicializar();
	scanf("%d", &n);
	lerDados();
	Processar();
	Limpar();
	return 0;
}
