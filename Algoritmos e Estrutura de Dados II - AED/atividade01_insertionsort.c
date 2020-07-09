#include <stdio.h>

int *InsertionSort(int ordenar[], int tam)
{
    int i;
	for (i = 1; i < tam; i++)
	{
		int j = i - 1, current = ordenar[i];
		while (j >= 0 && current < ordenar[j])
		{
			ordenar[j + 1] = ordenar[j];
			j--;
		}
		ordenar[j + 1] = current;
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
	vetor = InsertionSort(vetor, tam);
	for (i = 0; i < tam; i++)
	{
		printf("%d ", vetor[i]);
	}
}
