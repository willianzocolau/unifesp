#include <stdio.h>

int Pai(int i){
	return (i / 2);
}

int Filho_Esquerdo(int i){
	return (i * 2);
}

int Filho_Direito(int i){
	return (i * 2) + 1;
}

int Troca(int ordenar[], int i, int pai)
{
	int aux = ordenar[i];
	ordenar[i] = ordenar[pai];
	ordenar[pai] = aux;
}

void Imprimir(int ordenar[], int tam)
{
	int i;
	for (i = 1; i <= tam; i++)
	{
		printf("%d ", ordenar[i]);
	}
	printf("\n");
}

int Refazer(int ordenar[], int i, int tam)
{
	int pai = i;
	int esq = Filho_Esquerdo(i);
	int dir = Filho_Direito(i);
	if (esq <= tam && ordenar[esq] > ordenar[pai])
	{
		pai = esq;
	}
	if (dir <= tam && ordenar[dir] > ordenar[pai])
	{
		pai = dir;
	}
	if (pai != i)
	{
		Troca(ordenar, i, pai);
		Refazer(ordenar, pai, tam);
	}
}

int Construir(int ordenar[], int tam)
{
	int i;
	for (i = ((tam) / 2); i >= 1; i--)
	{
		Refazer(ordenar, i, tam);
	}
}

void HeapSort(int ordenar[], int tam)
{
	Refazer(ordenar, 1, tam);
	Imprimir(ordenar, tam);
	Construir(ordenar, tam);
	Imprimir(ordenar, tam);

	int i, aux_tam = tam;
	for (i = aux_tam; i > 1; i--) {
		Troca(ordenar, 1, i);
		aux_tam--;
		Refazer(ordenar, 1, aux_tam);
	}

	Imprimir(ordenar, tam);
}

int main()
{
	int tam, i;
	scanf("%d", &tam);
	int *vetor = (int*)malloc(sizeof(int)*tam * 100);
	for (i = 1; i <= tam; i++)
	{
		scanf("%d", &vetor[i]);
	}
	HeapSort(vetor, tam);
	return 0;
}
