#include <stdio.h>
#include <stdlib.h>

typedef struct Raiz
{
	int identificacao;
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

TRaiz* AlocarRaiz();
TArvore* AlocarArvore();
void Inicializar();
TRaiz** Pesquisar(TRaiz **raiz, int identificacao);
TRaiz* Remover(TRaiz **raiz, int identificacao);
void Inserir(TRaiz **raiz, int identificacao);
void Limpar(TRaiz **raiz);
void Imprimir(TRaiz **raiz);
void Processar();

TRaiz* AlocarRaiz()
{
	TRaiz *novo = (TRaiz*)malloc(sizeof(TRaiz));
	novo->identificacao = -1;
	novo->direita = NULL;
	novo->esquerda = NULL;
	return novo;
}

TArvore* AlocarArvore()
{
	TArvore *novo = (TArvore*)malloc(sizeof(TArvore));
	novo->raiz = NULL;
	novo->tamanho = 0;
	return novo;
}

void Inicializar()
{
	pArvore = AlocarArvore();
}

int existe;
TRaiz** Pesquisar(TRaiz **raiz, int identificacao)
{
	if ((*raiz) != NULL)
	{
		if (identificacao == (*raiz)->identificacao)
		{
			existe = 1;
		}
		if (identificacao > (*raiz)->identificacao)
		{
			Pesquisar(&(*raiz)->direita, identificacao);
		}
		else
		{
			Pesquisar(&(*raiz)->esquerda, identificacao);
		}
	}
	else
	{
		return raiz;
	}
}

TRaiz* Remover(TRaiz **raiz, int identificacao)
{
	if ((*raiz) == NULL){ return NULL; }
	else
	{
		if (identificacao > (*raiz)->identificacao)
		{
			(*raiz)->direita = Remover(&(*raiz)->direita, identificacao);
		}
		else if (identificacao < (*raiz)->identificacao)
		{
			(*raiz)->esquerda = Remover(&(*raiz)->esquerda, identificacao);
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
				(*raiz)->identificacao = temp->identificacao;
				temp->identificacao = identificacao;
				(*raiz)->direita = Remover(&(*raiz)->direita, identificacao);
			}
		}
		return (*raiz);
	}
}

int x = 0;
void Inserir(TRaiz **raiz, int identificacao)
{
	(*raiz) = AlocarRaiz();
	(*raiz)->identificacao = identificacao;
	(*raiz)->direita = NULL;
	(*raiz)->esquerda = NULL;
}

void Limpar(TRaiz **raiz)
{
	if ((*raiz) != NULL)
	{
		Limpar(&(*raiz)->esquerda);
		Limpar(&(*raiz)->direita);
		free((*raiz));
	}
}

void Processar()
{
	int entrada, remover, verificar;
	do
	{
		scanf("%d", &entrada);
		if (entrada != -1)
		{
			existe = 0;
			TRaiz **raiz = Pesquisar(&pArvore->raiz, entrada);
			Inserir(&(*raiz), entrada);
			pArvore->tamanho++;
		}
		verificar = entrada;
	} while (verificar != -1);
	existe = 0;
	scanf("%d", &remover);
	Pesquisar(&pArvore->raiz, remover);
	if (existe == 1)
	{
		Remover(&pArvore->raiz, remover);
		pArvore->tamanho--;
	}
	else
	{
		TRaiz **raiz = Pesquisar(&pArvore->raiz, entrada);
		Inserir(&(*raiz), remover);
		pArvore->tamanho++;
	}
	printf("%d", pArvore->tamanho);
	Limpar(&pArvore->raiz);
}

int main()
{
	Inicializar();
	Processar();
	return 0;
}
