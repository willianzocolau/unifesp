#include <stdio.h>
#include <stdlib.h>

//TAD.h
typedef struct Caracter
{
	char caracter;
	struct Caracter *proximo;
	struct Caracter *anterior;
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
void InserirNovaFrase(char caracter);
TCaracter* RemoverLetra(TCaracter *remover);
void Imprimir();
void Processar();

//TAD.c
TFrase *pNovaFrase = NULL;
TCaracter *pCursorEscrita = NULL;

TCaracter* AlocarCaracter()
{
	return (TCaracter*)malloc(sizeof(TCaracter));
}

TFrase* AlocarFrase()
{
	TFrase *pNovaFrase = (TFrase*)malloc(sizeof(TFrase));
	pNovaFrase->inicio = AlocarCaracter();
	pNovaFrase->fim = pNovaFrase->inicio;
	pNovaFrase->qtd_caracteres = 0;
	return pNovaFrase;
}

void Inicializar()
{
	pNovaFrase = AlocarFrase();
}

void InserirNovaFrase(char caracter)
{
	TCaracter *nova = AlocarCaracter();
	nova->caracter = caracter;
	if (pCursorEscrita == pNovaFrase->fim)
	{
		nova->anterior = pNovaFrase->fim;
		pNovaFrase->fim->proximo = nova;
		pNovaFrase->fim = nova;
		pNovaFrase->fim->proximo = pNovaFrase->inicio;
		pCursorEscrita = pNovaFrase->fim;
	}
	else if (pCursorEscrita == pNovaFrase->inicio)
	{
		nova->proximo = pCursorEscrita->proximo;
		pCursorEscrita->anterior = pNovaFrase->fim;
		nova->anterior = pCursorEscrita;
		pCursorEscrita->proximo->anterior = nova;
		pCursorEscrita->proximo = nova;
		pCursorEscrita = nova;
	}
	else
	{
		nova->proximo = pCursorEscrita->proximo;
		nova->anterior = pCursorEscrita;
		pCursorEscrita->proximo->anterior = nova;
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
	anterior = remover->anterior;
	anterior->proximo = remover->proximo;
	remover->proximo->anterior = anterior;
	free(remover);
	pNovaFrase->qtd_caracteres--;
	return anterior;
}

void Processar()
{
	pCursorEscrita = pNovaFrase->inicio;
	char caracter;
	scanf("%c", &caracter);
	while (caracter != '\n')
	{
		if (caracter == '-')
		{
			if (pCursorEscrita != pNovaFrase->inicio)
			{
				pCursorEscrita = RemoverLetra(pCursorEscrita);
			}
		}
		else if (caracter == '[')
		{
			pCursorEscrita = pNovaFrase->inicio;
			pCursorEscrita->proximo = pNovaFrase->inicio->proximo;
		}
		else if (caracter == ']')
		{
			pCursorEscrita = pNovaFrase->fim;
			pCursorEscrita->anterior = pNovaFrase->fim->anterior;
			pCursorEscrita->proximo = pNovaFrase->inicio;
		}
		else if (caracter == '<')
		{
			if (pCursorEscrita != pNovaFrase->inicio)
			{
				pCursorEscrita = pCursorEscrita->anterior;
			}
		}
		else if (caracter == '>')
		{
			if (pCursorEscrita != pNovaFrase->fim)
			{
				pCursorEscrita = pCursorEscrita->proximo;
			}
		}
		else
		{
			InserirNovaFrase(caracter);
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
