#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define tam 10

//TAD.h
typedef struct Celula
{
	int id;
	char *nome;
	struct Celula *prox;
} TCelula;

TCelula *pDados = NULL;
TCelula *pDados_Aux = NULL;
int inicio;
int fim;

void TLista_Inicializar();
int TLista_IsEmpty();
void TLista_Inserir(int id, char *nome);
void TLista_Retirar(int id);
int TLista_Tamanho();
void lerDados(int n);
void Processar(int n, int k);
void Liberar();

//TAD.c
void TLista_Inicializar()
{
	pDados = (TCelula*)malloc(sizeof(TCelula) * tam);
	pDados_Aux = (TCelula*)malloc(sizeof(TCelula) * tam);
	inicio = 0;
	fim = 0;
}

int TLista_IsEmpty()
{
	if (inicio == fim){ return true; }
	else{ return false; }
}

void TLista_Inserir(int id, char *nome)
{
	TCelula *pDados_Novo = (TCelula*)malloc(sizeof(TCelula) * tam);
	(*pDados_Novo).id = id;
	(*pDados_Novo).nome = nome;
	if (inicio == fim)
	{
		pDados = pDados_Novo;
	}
	else
	{
		if (fim == 1)
		{
			(*pDados).prox = pDados_Novo;
		}
		if (pDados_Aux != NULL)
		{
			(*pDados_Aux).prox = pDados_Novo;
		}
		pDados_Aux = pDados_Novo;
	}
	fim++;
}

void TLista_Retirar(int id)
{
	int x = 0, indice=0,removido=false;
	TCelula *pDados_Eliminado = (TCelula*)malloc(sizeof(TCelula) * tam);
	for (x = inicio; x < fim; x++)
	{
		if (x == 0)
		{
			pDados_Aux = pDados;
			pDados_Eliminado = pDados;
		}
		else
		{
			(*pDados_Aux).id = indice;
			indice++;
			pDados_Eliminado = (*pDados_Eliminado).prox;
			if (indice != (fim - 1))
			{
				if (id != (*pDados_Eliminado).id)
				{
					pDados_Aux = pDados_Eliminado;
				}
			}
		}

		if (removido == false)
		{
			if (id == (*pDados_Eliminado).id)
			{
				printf("%s", (*pDados_Eliminado).nome);
				(*pDados_Aux).prox = (*pDados_Eliminado).prox;
				pDados_Aux = (*pDados_Aux).prox;
				free(pDados_Eliminado);
				pDados_Eliminado = pDados_Aux;
				removido = true;
				if (id == 0)
				{
					pDados = pDados_Aux;
				}
			}
		}
	}
	fim--;
	if (TLista_Tamanho() >= 1)
	{
		printf("\n");
	}
}

int TLista_Tamanho()
{
	return (fim - inicio);
}

void lerDados(int n)
{
	int x = 0;
	for (x = 0; x < n; x++)
	{
		char *nome = (char*)malloc(sizeof(char) * tam);
		scanf("%s", nome);
		TLista_Inserir(x, nome);
	}
}

void Processar(int n, int k)
{
	int queimado = 0;
	while (TLista_IsEmpty() == false)
	{
		int contador = 0;
		if (queimado == TLista_Tamanho()){ queimado = inicio; }
		while (contador < k)
		{
			if (queimado > TLista_Tamanho()){ queimado = inicio; }
			queimado++;
			if (queimado == TLista_Tamanho()){ queimado = inicio; }
			contador++;
		}
		TLista_Retirar(queimado);
	}
}

void Liberar()
{
	free(pDados);
	free(pDados_Aux);
}

int main()
{
	int n = 0, k = 0;
	scanf("%d %d", &n, &k);
	TLista_Inicializar();
	lerDados(n);
	Processar(n, k);
	Liberar();
	return 1;
}
