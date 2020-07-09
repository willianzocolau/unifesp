#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int cod_unidade;
	int num_alunos;
	int qtd_presenca;
} ddUnidade;

typedef struct
{
	int cod_unidade;
	int num_matricula;
} ddCongresso;

void lerDados_Unidades(int num_unidades, ddUnidade *pDados_Unidade)
{
	int x = 0;
	for (x = 0; x<num_unidades; x++)
	{
		scanf("%d %d", &pDados_Unidade[x].cod_unidade, &pDados_Unidade[x].num_alunos);
	}
}

int lerDados_Congresso(int num_blocos, ddCongresso *pDados_Congresso)
{
	int x = 0, controle = 1, realocar = 1;
	for (x = 0; x<controle; x++)
	{
		scanf("%d", &pDados_Congresso[x].cod_unidade);
		if (pDados_Congresso[x].cod_unidade == -1)
		{
			break;
		}
		scanf("%d", &pDados_Congresso[x].num_matricula);
		if (realocar == num_blocos)
		{
			pDados_Congresso = (ddCongresso*)realloc(pDados_Congresso, (sizeof(pDados_Congresso) * num_blocos));
			realocar=1;
		}
		controle++;
		realocar++;
	}
	return x;
}

void Processar(int num_unidades, int qtd_congresso, ddCongresso *pDados_Congresso, ddUnidade *pDados_Unidade)
{
	int x = 0, y = 0, qtd = 0, cod = 0;
	double res = 0, menor = 0;
	for (x = 0; x<num_unidades; x++)
	{
		qtd = 0;
		for (y = 0; y<qtd_congresso; y++)
		{
			if (pDados_Unidade[x].cod_unidade == pDados_Congresso[y].cod_unidade)
			{
				qtd++;
			}
		}

		pDados_Unidade[x].qtd_presenca = qtd;
	}

	for (x = 0; x<num_unidades; x++)
	{
		res = 0;
		res = ((double)pDados_Unidade[x].qtd_presenca / (double)pDados_Unidade[x].num_alunos);
		if (x == 0)
		{
			cod = pDados_Unidade[x].cod_unidade;
			menor = res;
		}
		else if (menor > res)
		{
			cod = pDados_Unidade[x].cod_unidade;
			menor = res;
		}
	}

	printf("%d\n", cod);
	for (x = 0; x<qtd_congresso; x++)
	{
		if (pDados_Congresso[x].cod_unidade == cod)
		{
			printf("%d\n", pDados_Congresso[x].num_matricula);
		}
	}
}

int main()
{
	int num_unidades, num_blocos, qtd_congresso;
	scanf("%d", &num_unidades);
	ddUnidade* pDados_Unidade = (ddUnidade*)malloc(sizeof(ddUnidade) * num_unidades);
	lerDados_Unidades(num_unidades, pDados_Unidade);
	scanf("%d", &num_blocos);
	ddCongresso* pDados_Congresso = (ddCongresso*)malloc(sizeof(ddCongresso) * num_blocos);
	qtd_congresso = lerDados_Congresso(num_blocos, pDados_Congresso);
	Processar(num_unidades,qtd_congresso,pDados_Congresso,pDados_Unidade);
	free(pDados_Unidade);
	free(pDados_Congresso);
}
