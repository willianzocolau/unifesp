#include <stdio.h>

int *SelectionSort(int ordenar[], int tam)
{
	int i;
	for (i = 0; i < (tam - 1); i++)
	{
		int j = i + 1, current = i, aux;
		while (j < tam)
		{
			if (ordenar[current] > ordenar[j])
			{
				current = j;
			}
			j++;
		}

		if (current != i)
		{
			aux = ordenar[i];
			ordenar[i] = ordenar[current];
			ordenar[current] = aux;
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