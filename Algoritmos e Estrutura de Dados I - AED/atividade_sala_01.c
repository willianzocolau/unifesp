#include <stdio.h>
#include <stdlib.h>

//TAD.h
typedef struct
{
	char entrada[50];
	float valor[50];
	int topo;
	int qtd_operadores;
} ddCalculadora;

//TAD.c
void lerDados_Expressao(ddCalculadora *pDados)
{
	int x = 0, qtd_operadores = 0;
	for (x = 0; x < 50; x++)
	{
		char caracter;
		scanf("%c", &caracter);
		if (caracter != '\n')
		{
			if ((caracter == '+') || (caracter == '-') || (caracter == '*') || (caracter == '/'))
			{
				qtd_operadores++;
			}
			pDados[0].entrada[x] = caracter;
		}
		else
		{
			pDados[0].qtd_operadores = qtd_operadores;
			pDados[0].topo = x;
			break;
		}
	}
}

void lerDados_Valores(ddCalculadora *pDados)
{
	int x = 0;
	for (x = 0; x < pDados[0].topo; x++)
	{
		if (!((pDados[0].entrada[x] == '+') || (pDados[0].entrada[x] == '-') || (pDados[0].entrada[x] == '*') || (pDados[0].entrada[x] == '/')))
		{
			scanf("%f", &pDados[1].valor[x]);
		}
	}
}

ddCalculadora* desempilharDados(ddCalculadora *pDados, int indice)
{
	int x = 0, y = 0;
	ddCalculadora *pDados_Novo = (ddCalculadora*)malloc(((sizeof(ddCalculadora)) * 2));
	pDados_Novo[0].qtd_operadores = (pDados[0].qtd_operadores - 1);
	pDados_Novo[0].topo = (pDados[0].topo - 2);
	for (x = 0; x <= pDados[0].topo; x++)
	{
		if ((x != (indice + 1)) && (x != (indice - 1)))
		{
			pDados_Novo[0].entrada[y] = pDados[0].entrada[x];
			pDados_Novo[1].valor[y] = pDados[1].valor[x];
			y++;
		}
	}
	free(pDados);
	return pDados_Novo;
}

ddCalculadora* Calcular(ddCalculadora *pDados)
{
	int x = 0;
	for (x = 0; x <= pDados[0].topo; x++)
	{
		float total = 0;
		int validador = 0;
		if (
			(pDados[0].entrada[x] != '+') &&
			(pDados[0].entrada[x] != '-') &&
			(pDados[0].entrada[x] != '*') &&
			(pDados[0].entrada[x] != '/')
			)
		{
			if (pDados[0].entrada[x - 1] == '+')
			{
				total = pDados[1].valor[x + 1] + pDados[1].valor[x];
				validador = 1;
			}
			else if (pDados[0].entrada[x - 1] == '-')
			{
				total = pDados[1].valor[x + 1] - pDados[1].valor[x];
				validador = 1;
			}
			else if (pDados[0].entrada[x - 1] == '*')
			{
				total = pDados[1].valor[x + 1] * pDados[1].valor[x];
				validador = 1;
			}
			else if (pDados[0].entrada[x - 1] == '/')
			{
				total = pDados[1].valor[x + 1] / pDados[1].valor[x];
				validador = 1;
			}
		}

		if (validador == 1)
		{
			pDados[1].valor[x] = total;
			pDados = desempilharDados(pDados, x);
			x = 0;
		}
	}
	return pDados;
}

int main()
{
	ddCalculadora *pDados = (ddCalculadora*)malloc(sizeof(ddCalculadora));
	lerDados_Expressao(pDados);
	lerDados_Valores(pDados);
	pDados = Calcular(pDados);
	printf("%f", pDados[1].valor[0]);
	free(pDados);
	return 0;
}

