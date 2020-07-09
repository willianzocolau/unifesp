#include <stdio.h>
#include <stdlib.h>

//TADArvore.h
typedef struct Raiz
{
	int identificacao;
	struct Raiz *direita;
	struct Raiz *esquerda;
} TRaiz;

typedef struct Arvore
{
	struct Raiz *raiz;
} TArvore;

typedef struct Ordem
{
	int *lista;
} TOrdem;

TArvore *pArvore;
TOrdem *pOrdem;
int t;

TRaiz* AlocarRaiz();
TArvore* AlocarArvore();
TOrdem* AlocarOrdem();
int* AlocarLista();
void Inicializar();
int BuscarIndiceRaiz(int identificacao);
void Percorrer(TRaiz **raiz);
void Construir(TRaiz **raiz, int esquerda, int direita);
void Limpar(TRaiz **raiz);
void LerDados();
void Processar();

//TADArvore.c
TRaiz* AlocarRaiz()
{
	TRaiz *novo = (TRaiz*)malloc(sizeof(TRaiz));
	novo->identificacao = -1;
	novo->direita = NULL;
	novo->esquerda = NULL;
	return novo;
}

TArvore* AlocarArvore()
{
	TArvore *novo = (TArvore*)malloc(sizeof(TArvore));
	novo->raiz = NULL;
	return novo;
}

TOrdem* AlocarOrdem()
{
	return (TOrdem*)malloc(sizeof(TOrdem));
}

int* AlocarLista()
{
	return (int*)malloc(sizeof(int)*t);
}

void Inicializar()
{
	pArvore = AlocarArvore();
	pOrdem = AlocarOrdem();
}

int BuscarIndiceRaiz(int identificacao)
{
	int i;
	for (i = 0; i < t; i++)
	{
		if (pOrdem[1].lista[i] == identificacao)
		{
			return i;
		}
	}
	return -1;
}

void Percorrer(TRaiz **raiz)
{
	if ((*raiz) != NULL)
	{
		Percorrer(&(*raiz)->esquerda);
		Percorrer(&(*raiz)->direita);
		printf("%d\n", (*raiz)->identificacao);
	}
}

int x = 0;
void Construir(TRaiz **raiz, int esquerda, int direita)
{
	if (esquerda > direita || x == t){ return; }
	int indice = BuscarIndiceRaiz(pOrdem[0].lista[x]);
	TRaiz *novo = AlocarRaiz();
	novo->identificacao = pOrdem[0].lista[x];
	novo->direita = NULL;
	novo->esquerda = NULL;
	(*raiz) = novo;
	x++;
	if (esquerda == direita){return;}
	Construir(&(*raiz)->esquerda, esquerda, indice - 1);
	Construir(&(*raiz)->direita, indice + 1, direita);
}

void Limpar(TRaiz **raiz)
{
	if ((*raiz) != NULL)
	{
		Limpar(&(*raiz)->esquerda);
		Limpar(&(*raiz)->direita);
		free((*raiz));
	}
}

void LerDados()
{
	int i, j;
	for (i = 0; i < 2; i++)
	{
		pOrdem[i].lista = AlocarLista();
		for (j = 0; j < t; j++)
		{
			scanf("%d", &pOrdem[i].lista[j]);
		}
	}
}

void Processar()
{
	Construir(&pArvore->raiz, 0, t);
	Percorrer(&pArvore->raiz);
	Limpar(&pArvore->raiz);
}

//Main.c
int main()
{
	scanf("%d", &t);
	Inicializar();
	LerDados();
	Processar();
	return 0;
}
