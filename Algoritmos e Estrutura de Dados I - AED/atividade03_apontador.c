#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//TAD.h
typedef struct Celula
{
	int indice;
	float forca;
	float forca_inicial;
	struct Celula *prox;
} TCelula;

TCelula *inicio;
TCelula *fim;

void Inicilizar();
void lerDados(int n);
void ProcessarDados(int n, float k);

//TAD.c
void Inicilizar()
{
	inicio = (TCelula*)malloc(sizeof(TCelula));
	fim = (TCelula*)malloc(sizeof(TCelula));
}

void lerDados(int n)
{
	int x = 0;
	TCelula *pDados_Aux = (TCelula*)malloc(sizeof(TCelula));
	pDados_Aux = NULL;
	for (x = 0; x < n; x++)
	{
		float forca = 0;
		scanf("%f", &forca);
		TCelula *pDados_Novo = (TCelula*)malloc(sizeof(TCelula));
		(*pDados_Novo).indice = x;
		(*pDados_Novo).forca = forca;
		(*pDados_Novo).forca_inicial = forca;
		if (x == 0)
		{
			inicio = pDados_Novo;
		}
		else
		{
			if (x == 1)
			{
				(*inicio).prox = pDados_Novo;
			}
			if (pDados_Aux != NULL)
			{
				(*pDados_Aux).prox = pDados_Novo;
			}
			pDados_Aux = pDados_Novo;
		}

		if ((x + 1) == n)
		{
			fim = pDados_Novo;
		}
	}
}

void ProcessarDados(int n, float k)
{
	int x = 0;
	while (x != (n - 1))
	{
		TCelula *vencedor = (TCelula*)malloc(sizeof(TCelula));
		TCelula *perdedor = (TCelula*)malloc(sizeof(TCelula));
		float nova_forca;
		//Maior força - Primeiro oponente
		if (inicio->forca > inicio->prox->forca)
		{
			vencedor = inicio;
			perdedor = inicio->prox;
			//printf("\n\n 1 Caso - %d", vencedor);
		}
		//Maior força - Segundo oponente
		else if (inicio->forca < inicio->prox->forca)
		{
			vencedor = inicio->prox;
			perdedor = inicio;
			//printf("\n\n 2 Caso - %d", vencedor);
		}
		//Forças iguais - Primeiro oponente com menor indice
		else if (
			(inicio->forca == inicio->prox->forca) &&
			(inicio->indice < inicio->prox->indice)
			)
		{
			vencedor = inicio;
			perdedor = inicio->prox;
			//printf("\n\n 3 Caso - %d", vencedor);
		}
		//Forças iguais - Segundo oponente com menor indice
		else if (
			(inicio->forca == inicio->prox->forca) &&
			(inicio->indice > inicio->prox->indice)
			)
		{
			vencedor = inicio->prox;
			perdedor = inicio;
		}

		//Nova força
		nova_forca = vencedor->forca - perdedor->forca + k;
		if (nova_forca > vencedor->forca_inicial)
		{
			nova_forca = vencedor->forca_inicial;
		}
		vencedor->forca = nova_forca;

		//Controle inicio e fim
		fim->prox = vencedor;
		fim = vencedor;
		inicio = inicio->prox->prox;
		x++;
	}
	printf("%d", (inicio->indice + 1));
	free(inicio);
	free(fim);
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
	return 0;
}
