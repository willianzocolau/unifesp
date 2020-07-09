
#include <stdio.h>
#include <stdlib.h>

//TADArvore.h
typedef struct Raiz
{
	int identificacao;
	struct Raiz *direita;
	struct Raiz *esquerda;
} TRaiz;

typedef struct Arvore
{
	struct Raiz *raiz;
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

//TADArvore.c
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
			if ((*raiz)->esquerda == NULL && (*raiz)->direita == NULL)//Nó folha
			{
				free((*raiz));
				(*raiz) = NULL;
			}
			else if ((*raiz)->direita == NULL)//Somente filho a esquerda
			{
				TRaiz* t = (*raiz);
				(*raiz) = (*raiz)->esquerda;
				free(t);
			}
			else if ((*raiz)->esquerda == NULL)//Somente filho a direita
			{
				TRaiz* t = (*raiz);
				(*raiz) = (*raiz)->direita;
				free(t);
			}
			else//Tem ambos os filhos
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

void Imprimir(TRaiz **raiz)
{
	if ((*raiz) != NULL){
		printf("(C%d", (*raiz)->identificacao);
		Imprimir(&(*raiz)->esquerda);
		Imprimir(&(*raiz)->direita);
		printf(")");
	}
	else
	{
		printf("()");
	}
}

void Processar()
{
	int i, entrada, remover;
	for (i = 0; i < t; i++)
	{
		existe = 0;
		scanf("%d", &entrada);
		TRaiz **raiz = Pesquisar(&pArvore->raiz, entrada);
		if (existe == 0)
		{
			Inserir(&(*raiz), entrada);
		}
	}
	existe = 0;
	scanf("%d", &remover);
	Remover(&pArvore->raiz, remover);
	if (existe == 0)
	{
		TRaiz **raiz = Pesquisar(&pArvore->raiz, remover);
		if (existe == 0)
		{
			Inserir(&(*raiz), remover);
		}
	}
	Imprimir(&pArvore->raiz);
	Limpar(&pArvore->raiz);
}

//Main.c
int main()
{
	scanf("%d", &t);
	Inicializar();
	Processar();
	return 0;
}
