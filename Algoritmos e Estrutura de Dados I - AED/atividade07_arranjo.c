#include <stdio.h>
#include <stdlib.h>

//TADArvore.h
typedef struct Arvore
{
	int *filhos;
} TArvore;

TArvore *pLinhagem;
int n, m, *qtd_filhos;

TArvore* AlocarArvore();
int* AlocarFilho();
void Inicializar();
void AdicionarFilho(int pai, int filho);
void Processar();
void Imprimir(int pai);
void Limpar();

//TADArvore.c
TArvore* AlocarArvore()
{
	return (TArvore*)malloc(sizeof(TArvore)*n);
}

int* AlocarFilho()
{
	return (int*)malloc(sizeof(int)*n);
}

void Inicializar()
{
	qtd_filhos = (int*)malloc(sizeof(int)*n);
	pLinhagem = AlocarArvore();
	int i;
	for (i = 0; i < n; i++)
	{
		pLinhagem[i].filhos = AlocarFilho();
		qtd_filhos[i] = 0;
	}
}

void AdicionarFilho(int pai, int filho)
{
	pLinhagem[pai].filhos[qtd_filhos[pai]] = filho;
	qtd_filhos[pai]++;
}

void Processar()
{
	int i, identificacao_pai, identificacao_filho;
	for (i = 0; i < m; i++)
	{
		scanf("%d %d", &identificacao_pai, &identificacao_filho);
		AdicionarFilho(identificacao_pai - 1, identificacao_filho - 1);
	}
}

void Imprimir(int pai)
{
	int i;
	printf("(%d", pai + 1);
	for (i = 0; i < qtd_filhos[pai]; i++)
	{
		Imprimir(pLinhagem[pai].filhos[i]);
	}
	printf(")");
}

void Limpar()
{
	free(pLinhagem);
}

//Main.c
int main()
{
	scanf("%d %d", &n, &m);
	Inicializar();
	Processar();
	Imprimir(0);
	Limpar();
	return 0;
}
