#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int chave;
} TItem;

typedef struct
{
	TItem *item;
	int tamanho;
	int max_tam;
} Dicionario;

Dicionario* Inicializar(Dicionario *vetor)
{
	vetor = (Dicionario*)malloc(sizeof(Dicionario));
	vetor->item = (TItem*)malloc(sizeof(TItem));
	vetor->tamanho = 0;
	vetor->max_tam = 0;
	return vetor;
}

int TDicionario_Pesquisa(Dicionario *vetor, TItem registro)
{
	int esq = 0, meio, dir = vetor->tamanho - 1;
	while (esq <= dir) {
		meio = (esq + dir) / 2;
		if (vetor->item[meio].chave == registro.chave) return meio;
		if (vetor->item[meio].chave < registro.chave) esq = meio + 1;
		else dir = meio - 1;
	}
	return -1;
}

void TDicionario_Insere(Dicionario *vetor, TItem registro)
{
	int j = vetor->tamanho - 1;
	if (vetor->tamanho > 0)
	{
		while (j >= 0 && registro.chave < vetor->item[j].chave)
		{
			vetor->item[j + 1].chave = vetor->item[j].chave;
			j--;
		}
	}
	vetor->item[j + 1].chave = registro.chave;
	vetor->tamanho++;
	vetor->max_tam++;
}

int TDicionario_Remove(Dicionario *vetor, TItem registro)
{
	int indice_chave = TDicionario_Pesquisa(vetor, registro), removido = 0;
	if (indice_chave > 0)
	{
		vetor->item[indice_chave].chave = vetor->item[vetor->tamanho].chave;
		vetor->tamanho--;
		removido = 1;
	}
	return removido;
}

void TDicionario_Finalizar(Dicionario *vetor)
{
	free(vetor);
}

void Read_Vetor(Dicionario *vetor)
{
	int verificar = 0;
	do
	{
		TItem registro;
		scanf("%d", &registro.chave);
		if (registro.chave != -1)
		{
			TDicionario_Insere(vetor, registro);
		}
		verificar = registro.chave;
	} while (verificar != -1);
}

int main()
{
	TItem registro;
	Dicionario *vetor = NULL;
	vetor = Inicializar(vetor);
	Read_Vetor(vetor);
	scanf("%d", &registro.chave);
	int removido = TDicionario_Remove(vetor, registro);
	if (removido == 0)
	{
		TDicionario_Insere(vetor, registro);
	}
	printf("%d", vetor->tamanho);
	TDicionario_Finalizar(vetor);
	return 0;
}
