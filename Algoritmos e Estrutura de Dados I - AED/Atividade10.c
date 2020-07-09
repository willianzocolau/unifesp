#include <stdio.h>
#include <stdlib.h>

//TADHeap.h
typedef struct
{
	int *fila;
	int tamanho;
} TFilaPrioridade;

TFilaPrioridade *pArvore;
int n;

int TFilaPrioridade_Pai(int i);
TFilaPrioridade* TFilaPrioridade_Alocar();
int* TFilaPrioridade_AlocarFila();
void TFilaPrioridade_Inicia();
int TFilaPrioridade_DesceHeap(int pai, int filho);
void TFilaPrioridade_SobeHeap(int i);
int TFilaPrioridade_Insere(int i, int elemento);
void Processar();
void Liberar();

//TADHeap.c
int TFilaPrioridade_Pai(int i){
	return (i / 2);
}

TFilaPrioridade* TFilaPrioridade_Alocar()
{
	return (TFilaPrioridade*)malloc(sizeof(TFilaPrioridade));
}

int* TFilaPrioridade_AlocarFila()
{
	return (int*)malloc(sizeof(int)*n);
}

void TFilaPrioridade_Inicia()
{
	pArvore = TFilaPrioridade_Alocar();
	pArvore->tamanho = 0;
	pArvore->fila = TFilaPrioridade_AlocarFila();
}

int TFilaPrioridade_DesceHeap(int pai, int filho)
{
	int aux = pArvore->fila[pai];
	pArvore->fila[pai] = pArvore->fila[filho];
	pArvore->fila[filho] = aux;
	return 1;
}

void TFilaPrioridade_SobeHeap(int i)
{
	if (i == 1){ return; }
	while (i > 1 && pArvore->fila[TFilaPrioridade_Pai(i)] < pArvore->fila[i])
	{
		TFilaPrioridade_DesceHeap(TFilaPrioridade_Pai(i), i);
	}
	TFilaPrioridade_SobeHeap(i - 1);
}

int TFilaPrioridade_Insere(int i, int elemento)
{
	pArvore->fila[i] = elemento;
	pArvore->tamanho++;
	return 1;
}

void Processar()
{
	int i, elemento;

	//Inserir sem ordem
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &elemento);
		TFilaPrioridade_Insere(i, elemento);
	}

	//Construir Heap Máximo
	for (i = pArvore->tamanho; i > 1 ; i--)
	{
		TFilaPrioridade_SobeHeap(i);
		int aux = pArvore->fila[1];
		pArvore->fila[1] = pArvore->fila[i];
		pArvore->fila[i] = aux;
	}

	//Calcula o custo
	int custo,op = pArvore->fila[1] + pArvore->fila[2];
	custo = op;
	for (i = 3; i <= pArvore->tamanho; i++)
	{
		op += pArvore->fila[i];
		custo += op;
	}
	printf("%d", custo);
}

void Liberar()
{
	free(pArvore);
}

//Main.c
int main()
{
	TFilaPrioridade_Inicia();
	scanf("%d", &n);
	Processar();
	Liberar();
	return 0;
}
