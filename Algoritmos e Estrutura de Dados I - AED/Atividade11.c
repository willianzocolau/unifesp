#include <stdio.h>
#include <stdlib.h>

typedef int TChave;

typedef struct
{
	TChave Chave;
}TItem;

typedef struct
{
	TItem Item;
	int Esq, Dir;
} TNo;

typedef struct
{
	TNo *No;
	int Tamanho;
} TArvBin;

TArvBin *pArvore;

TArvBin* Alocar_Arvore()
{
	return (TArvBin*)malloc(sizeof(TArvBin));
}

TNo* Alocar_Raiz()
{
	return (TNo*)malloc(sizeof(TNo));
}

void Inicializar()
{
	pArvore = Alocar_Arvore();
	pArvore->No = Alocar_Raiz();
	pArvore->Tamanho = 0;
}

TItem Ler_Dados()
{
	TItem item_buscar;
	fread(&item_buscar, sizeof(TItem), 1, stdin);
	TItem item;
	int esquerda, direita;
	while (fread(&item, sizeof(TItem), 1, stdin) > 0)
	{
		//Esquerda
		fread(&esquerda, sizeof(int), 1, stdin);
		//Direita
		fread(&direita, sizeof(int), 1, stdin);
		pArvore->No[pArvore->Tamanho].Item = item;
		pArvore->No[pArvore->Tamanho].Esq = esquerda;
		pArvore->No[pArvore->Tamanho].Dir = direita;
		pArvore->Tamanho++;
	}
	pArvore->Tamanho--;
	return item_buscar;
}

int existe = 0;
void Buscar(int indice, TItem item_buscar)
{
	if (pArvore->No[indice].Item.Chave == item_buscar.Chave)
	{
		existe = 1;
		return;
	}
	else if (pArvore->No[indice].Esq != -1)
	{
		Buscar(pArvore->No[indice].Esq, item_buscar);
	}
	if (pArvore->No[indice].Dir != -1)
	{
		Buscar(pArvore->No[indice].Dir, item_buscar);
	}
}

void Processar()
{
	TItem item_buscar = Ler_Dados();
	Buscar(0, item_buscar);
	printf("%d", existe);
}

void Liberar()
{
	free(pArvore);
}

//Main.c
int main()
{
	Inicializar();
	Processar();
	Liberar();
}
