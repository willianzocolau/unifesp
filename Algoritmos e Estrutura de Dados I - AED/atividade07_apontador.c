#include <stdio.h>
#include <stdlib.h>

//TADArvore.h
typedef struct Arvore
{
	int identificacao;
	int ultimo;
	struct Arvore *pai;
	struct Arvore *primeiro_filho;
	struct Arvore *proximo_irmao;
	struct Arvore *ultimo_irmao;
} TArvore;

TArvore *pLinhagem;
TArvore *buscar_pai;
int n, m;

TArvore* AlocarArvore();
void Inicializar();
void AdicionarFilho(TArvore *pai, int identificacao);
void BuscarArvore(TArvore *arvore, int identificacao);
void Processar();
void Limpar(TArvore *arvore);

//TADArvore.c
TArvore* AlocarArvore()
{
	TArvore *novo = (TArvore*)malloc(sizeof(TArvore));
	novo->pai = NULL;
	novo->primeiro_filho = NULL;
	novo->proximo_irmao = NULL;
	novo->ultimo_irmao = NULL;
	return novo;
}

void Inicializar()
{
	pLinhagem = AlocarArvore();
	pLinhagem->identificacao = 1;
}

void AdicionarFilho(TArvore *pai, int identificacao)
{
	TArvore *novo_filho = AlocarArvore();
	novo_filho->identificacao = identificacao;
	novo_filho->pai = pai;
	novo_filho->ultimo = 1;
	//Árvore recebida é do pai, pois não tem filhos ainda.
	if (pai->primeiro_filho == NULL)
	{
		pai->primeiro_filho = novo_filho;
		pai->primeiro_filho->ultimo_irmao = novo_filho;
	}
	//Árvore recebida é do filho, pois o pai já tem filhos.
	else
	{
		pai->primeiro_filho->ultimo_irmao->ultimo = 0;
		pai->primeiro_filho->ultimo_irmao->proximo_irmao = novo_filho;
		pai->primeiro_filho->ultimo_irmao = novo_filho;
	}
}

void BuscarArvore(TArvore *arvore, int identificacao)
{
	if (arvore == NULL)
	{
		return;
	}
	else if (arvore->identificacao == identificacao)
	{
		buscar_pai = arvore;
	}
	BuscarArvore(arvore->proximo_irmao, identificacao);
	BuscarArvore(arvore->primeiro_filho, identificacao);
}

void Processar()
{
	int i, identificacao_pai, identificacao_filho;
	for (i = 0; i < m; i++)
	{
		scanf("%d %d", &identificacao_pai, &identificacao_filho);
		buscar_pai = NULL;
		BuscarArvore(pLinhagem, identificacao_pai);
		AdicionarFilho(buscar_pai, identificacao_filho);
	}
}

void Imprimir(TArvore *arvore)
{
	if (arvore == NULL){ return; }
	else{ printf("(%d", arvore->identificacao); }

	if (arvore->primeiro_filho == NULL)
	{
		printf(")");
	}
	else
	{
		Imprimir(arvore->primeiro_filho);
	}
	Imprimir(arvore->proximo_irmao);
	if (arvore->ultimo == 1)
	{
		printf(")");
	}
}

void Limpar(TArvore *arvore)
{
	if (arvore == NULL){ return; }
	else
	{
		Limpar(arvore->proximo_irmao);
		Limpar(arvore->primeiro_filho);
	}
	if (arvore != NULL)
	{
		free(arvore);
	}
}

//Main.c
int main()
{
	scanf("%d %d", &n, &m);
	Inicializar();
	Processar();
	Imprimir(pLinhagem);
	Limpar(pLinhagem);
	return 0;
}

