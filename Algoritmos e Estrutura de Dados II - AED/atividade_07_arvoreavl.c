#include <stdio.h>
#include <stdlib.h>

typedef struct Registro
{
	int chave;
} TRegistro;

typedef struct Raiz
{
	TRegistro item;
	struct Raiz *direita;
	struct Raiz *esquerda;
} TRaiz;

typedef struct Arvore
{
	struct Raiz *raiz;
	int tamanho;
} TArvore;

TArvore *pArvore;
int t;

TRaiz* TArvore_AlocarRaiz();
TArvore* TArvore_AlocarArvore();
void TArvore_Inicializar();
TRaiz** TArvore_Pesquisar(TRaiz **raiz, TRegistro registro);
TRaiz* TArvore_Remover(TRaiz **raiz, TRegistro registro);
void TArvore_Inserir(TRaiz **raiz, TRegistro registro);
void TArvore_Limpar(TRaiz **raiz);
void TArvore_Imprimir(TRaiz **raiz);

TRaiz* TArvore_AlocarRaiz()
{
	TRaiz *novo = (TRaiz*)malloc(sizeof(TRaiz));
	novo->item.chave = -1;
	novo->direita = NULL;
	novo->esquerda = NULL;
	return novo;
}

TArvore* TArvore_AlocarArvore()
{
	TArvore *novo = (TArvore*)malloc(sizeof(TArvore));
	novo->raiz = NULL;
	novo->tamanho = 0;
	return novo;
}

void TArvore_Inicializar()
{
	pArvore = AlocarArvore();
}

int existe;
TRaiz** TArvore_Pesquisar(TRaiz **raiz, TRegistro registro)
{
	if ((*raiz) != NULL)
	{
		if (registro.chave == (*raiz)->item.chave)
		{
			existe = 1;
		}
		if (registro.chave > (*raiz)->item.chave)
		{
			Pesquisar(&(*raiz)->direita, registro);
		}
		else
		{
			Pesquisar(&(*raiz)->esquerda, registro);
		}
	}
	else
	{
		return raiz;
	}
}

TRaiz* TArvore_Remover(TRaiz **raiz, TRegistro registro)
{
	if ((*raiz) == NULL){ return NULL; }
	else
	{
		if (registro.chave > (*raiz)->item.chave)
		{
			(*raiz)->direita = Remover(&(*raiz)->direita, registro);
		}
		else if (registro.chave < (*raiz)->item.chave)
		{
			(*raiz)->esquerda = Remover(&(*raiz)->esquerda, registro);
		}
		else
		{
			existe = 1;
			if ((*raiz)->esquerda == NULL && (*raiz)->direita == NULL)
			{
				free((*raiz));
				(*raiz) = NULL;
			}
			else if ((*raiz)->direita == NULL)
			{
				TRaiz* t = (*raiz);
				(*raiz) = (*raiz)->esquerda;
				free(t);
			}
			else if ((*raiz)->esquerda == NULL)
			{
				TRaiz* t = (*raiz);
				(*raiz) = (*raiz)->direita;
				free(t);
			}
			else
			{
				TRaiz* temp = (*raiz)->direita;
				while (temp->esquerda != NULL)
				{
					temp = temp->esquerda;
				}
				(*raiz)->item.chave = temp->item.chave;
				temp->item.chave = registro.chave;
				(*raiz)->direita = Remover(&(*raiz)->direita, registro);
			}
		}
		return (*raiz);
	}
}

int x = 0;
void TArvore_Inserir(TRegistro registro)
{
	TRaiz **raiz = Pesquisar(&pArvore->raiz, registro);
	Inserir(&(*raiz), registro);
	pArvore->tamanho++;
	(*raiz) = AlocarRaiz();
	(*raiz)->item.chave = registro.chave;
	(*raiz)->direita = NULL;
	(*raiz)->esquerda = NULL;
}

void TArvore_Limpar(TRaiz **raiz)
{
	if ((*raiz) != NULL)
	{
		Limpar(&(*raiz)->esquerda);
		Limpar(&(*raiz)->direita);
		free((*raiz));
	}
}

int main()
{
	Inicializar();
	TArvore_Limpar(&pArvore->raiz);
	return 0;
}
