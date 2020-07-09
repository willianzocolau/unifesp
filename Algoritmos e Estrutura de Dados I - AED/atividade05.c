#include <stdio.h>
#include <stdlib.h>

//TAD.h
typedef struct Caracter
{
	int indice;
	char caracter;
	struct Caracter *proximo;
} TCaracter;

typedef struct Frase
{
	int qtd_caracteres;
	struct Caracter *inicio;
	struct Caracter *fim;
}TFrase;

TCaracter* AlocarCaracter();
TFrase* AlocarFrase();
void Inicializar();
TCaracter* BuscarCursor(int indice);
void AtualizarIndice();
void InserirNovaFrase(char caracter);
TCaracter* RemoverLetra(TCaracter *remover);
void Imprimir();
void Processar();

//TAD.c
TFrase *pNovaFrase = NULL;
TCaracter *pCursorEscrita = NULL;
int indice = 0;

TCaracter* AlocarCaracter()
{
	return (TCaracter*)malloc(sizeof(TCaracter));
}

TFrase* AlocarFrase()
{
	TCaracter *nova = (TCaracter*)malloc(sizeof(TCaracter));
	nova->indice = -1;
	TFrase *pNovaFrase = (TFrase*)malloc(sizeof(TFrase));
	pNovaFrase->inicio = nova;
	pNovaFrase->fim = nova;
	pNovaFrase->qtd_caracteres = 0;
	nova = NULL;
	free(nova);
	return pNovaFrase;

}

void Inicializar()
{
	pNovaFrase = AlocarFrase();
}

TCaracter* BuscarCursor(int indice)
{
	TCaracter *buscar;
	buscar = pNovaFrase->inicio;
	int i;
	for (i = 0; i <= pNovaFrase->qtd_caracteres; i++)
	{
		if (buscar->indice == indice)
		{
			break;
		}
		else
		{
			buscar = buscar->proximo;
		}
	}
	return buscar;
}

void AtualizarIndice()
{
	int novo_indice = 0;
	TCaracter *celula = pNovaFrase->inicio->proximo;
	celula->indice = novo_indice;
	novo_indice++;
	while (celula->proximo != pNovaFrase->inicio)
	{
		celula = celula->proximo;
		celula->indice = novo_indice;
		novo_indice++;
	}
	indice = novo_indice;
}

void InserirNovaFrase(char caracter)
{
	TCaracter *nova = AlocarCaracter();
	nova->caracter = caracter;
	if (pCursorEscrita == pNovaFrase->fim)
	{
		pNovaFrase->fim->proximo = nova;
		pNovaFrase->fim = nova;
		pNovaFrase->fim->proximo = pNovaFrase->inicio;
		pCursorEscrita = pNovaFrase->fim;
	}
	else
	{
		nova->proximo = pCursorEscrita->proximo;
		pCursorEscrita->proximo = nova;
		pCursorEscrita = nova;
	}
	pNovaFrase->qtd_caracteres++;
	nova = NULL;
	free(nova);
}

TCaracter* RemoverLetra(TCaracter *remover)
{
	TCaracter *anterior;
	anterior = BuscarCursor(remover->indice - 1);
	anterior->proximo = remover->proximo;
	free(remover);
	pNovaFrase->qtd_caracteres--;
	return anterior;
}

void Processar()
{
	char caracter;
	scanf("%c", &caracter);
	pCursorEscrita = pNovaFrase->inicio;
	while (caracter != '\n')
	{
		if (caracter == '-')
		{
			if (pCursorEscrita != pNovaFrase->inicio)
			{
				pCursorEscrita = RemoverLetra(pCursorEscrita);
				AtualizarIndice();
			}
		}
		else if (caracter == '[')
		{
			pCursorEscrita = pNovaFrase->inicio;
		}
		else if (caracter == ']')
		{
			pCursorEscrita = pNovaFrase->fim;
		}
		else if (caracter == '<')
		{
			if (pCursorEscrita != pNovaFrase->inicio)
			{
				pCursorEscrita = BuscarCursor(pCursorEscrita->indice - 1);
			}
		}
		else if (caracter == '>')
		{
			if (pCursorEscrita != pNovaFrase->fim)
			{
				pCursorEscrita = BuscarCursor(pCursorEscrita->indice + 1);
			}
		}
		else
		{
			InserirNovaFrase(caracter);
			AtualizarIndice();
		}
		scanf("%c", &caracter);
	}
}

void Imprimir()
{
	TCaracter *remover;
	int i;
	for (i = 0; i < pNovaFrase->qtd_caracteres; i++)
	{
		remover = pNovaFrase->inicio->proximo;
		printf("%c", pNovaFrase->inicio->proximo->caracter);
		pNovaFrase->inicio->proximo = pNovaFrase->inicio->proximo->proximo;
		free(remover);
	}
	free(pNovaFrase->inicio);
	free(pNovaFrase);
}

int main()
{
	Inicializar();
	Processar();
	Imprimir();
	return 0;
}
