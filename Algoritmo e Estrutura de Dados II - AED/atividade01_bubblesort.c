#include <stdio.h>

int *SelectionSort(int ordenar[], int tam)
{
	int i;
	for (i = 0; i < tam; i++)
	{
		int j = 0, current = i, aux;
		while (j < (tam - 1))
		{
			if (ordenar[j] > ordenar[j + 1])
			{
				aux = ordenar[j];
				ordenar[j] = ordenar[j + 1];
				ordenar[j + 1] = aux;
			}
			j++;
		}
	}
	return (int*)ordenar;
}

int main()
{
	int tam, i;
	scanf("%d", &tam);
	int *vetor = (int*)malloc(sizeof(int)*tam);
	for (i = 0; i < tam; i++)
	{
		scanf("%d", &vetor[i]);
	}
	vetor = SelectionSort(vetor, tam);
	for (i = 0; i < tam; i++)
	{
		printf("%d ", vetor[i]);
	}
}