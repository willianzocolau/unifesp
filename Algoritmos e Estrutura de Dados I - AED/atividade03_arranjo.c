#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//TAD.h
typedef struct Celula
{
	int indice;
	float forca;
	float forca_inicial;
} TCelula;

TCelula *pDados = NULL;
int inicio;
int fim;

void Inicilizar();
void lerDados(int n);
void ProcessarDados(int n,float k);

//TAD.c
void Inicilizar()
{
	inicio = 0;
	fim = 1;
	pDados = (TCelula*)malloc(sizeof(TCelula)*10000);
}

void lerDados(int n)
{
	int x = 0;
	for (x = 0; x < n; x++)
	{
		float forca = 0;
		scanf("%f", &forca);
		pDados[x].indice = x;
		pDados[x].forca = forca;
		pDados[x].forca_inicial = forca;
	}
}

void ProcessarDados(int n, float k)
{
	n--;
	fim = n;
	while (inicio != fim)
	{
		int vencedor = 0;
		int perdedor = 0;
		float nova_forca;
		//Maior força - Primeiro oponente
		if (pDados[inicio].forca > pDados[inicio + 1].forca)
		{
			vencedor = inicio;
			perdedor = inicio + 1;
			//printf("\n\n 1 Caso - %d", vencedor);
		}
		//Maior força - Segundo oponente
		else if (pDados[inicio].forca < pDados[inicio + 1].forca)
		{
			vencedor = inicio + 1;
			perdedor = inicio;
			//printf("\n\n 2 Caso - %d", vencedor);
		}
		//Forças iguais - Primeiro oponente com menor indice
		else if (
			(pDados[inicio].forca == pDados[inicio + 1].forca) &&
			(pDados[inicio].indice < pDados[inicio + 1].indice)
			)
		{
			vencedor = inicio;
			perdedor = inicio + 1;
			//printf("\n\n 3 Caso - %d", vencedor);
		}
		//Forças iguais - Segundo oponente com menor indice
		else if (
			(pDados[inicio].forca == pDados[inicio + 1].forca) &&
			(pDados[inicio].indice > pDados[inicio + 1].indice)
			)
		{
			vencedor = inicio + 1;
			perdedor = inicio;
		}

		//Nova força
		nova_forca = pDados[vencedor].forca - pDados[perdedor].forca + k;
		if (nova_forca > pDados[vencedor].forca_inicial)
		{
			nova_forca = pDados[vencedor].forca_inicial;
		}

		//Controle inicio e fim
		if (fim == n){ fim = 0; }
		else{ fim++; }
		if ((inicio + 2) >= n){ inicio = 0; }
		else{ inicio = inicio + 2; }

		pDados[fim].indice = pDados[vencedor].indice;
		pDados[fim].forca = nova_forca;
		pDados[fim].forca_inicial = pDados[vencedor].forca_inicial;
	}
	printf("%d", (pDados[inicio].indice + 1));
}

int main()
{
	int n = 0;
	float k = 0;
	scanf("%d %f", &n, &k);
	n = (int)pow(2, n);
	Inicilizar();
	lerDados(n);
	ProcessarDados(n, k);
	free(pDados);
	return 0;
}
