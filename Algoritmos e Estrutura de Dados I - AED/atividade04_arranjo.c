#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

//TAD.h
typedef struct Lista
{
	int id;
	char *nome;
} TLista;

TLista *pDados = NULL;
int inicio;
int fim;

void TLista_Inicializar();
int TLista_IsEmpty();
void TLista_Inserir(int id, char *nome);
void TLista_Retirar(int id);
void lerDados(int n);
void Processar(int n, int k);
int TLista_Tamanho();
void Liberar();

//TAD.c
void TLista_Inicializar()
{
	pDados = (TLista*)malloc(sizeof(TLista) * 100000);
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
	pDados[fim].id = id;
	pDados[fim].nome = nome;
	fim++;
}

void TLista_Retirar(int id)
{
	if (id == fim)
	{
		printf("%s", pDados[fim].nome);
		fim--;
	}
	else
	{
		int x = 0, indice = 0;
		for (x = inicio; x<fim; x++)
		{
			if (x == id)
			{
				printf("%s", pDados[x].nome);
			}
			else if (x != id)
			{
				pDados[indice].id = pDados[x].id;
				pDados[indice].nome = pDados[x].nome;
				indice++;
			}
		}
		fim--;
	}
	if(TLista_Tamanho() >= 1)
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
	    char *nome = (char*)malloc(sizeof(char));
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
