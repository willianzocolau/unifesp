#include <stdio.h>
#include <stdlib.h>
//TADArvoreAmigos.h
typedef struct RaizAmigos
{
	int identificacao;
	double grau;
	struct RaizAmigos *direita;
	struct RaizAmigos *esquerda;
} TRaizAmigos;
typedef struct Arvore
{
	struct RaizAmigos *raiz;
} TArvoreAmigos;
void TAvoreAmigos_Inicia();
void TArvoreAmigos_Pesquisar(TRaizAmigos **raiz, int identificacao);
void TArvoreAmigos_Buscar_Afinidade(TRaizAmigos **raiz, int identificacao);
void TArvoreAmigos_Inserir(TRaizAmigos **raiz, int identificacao, double grau);
void TArvoreAmigos_Limpar(TRaizAmigos **raiz);

//TADFilaPrioridade.h
typedef struct FilaPrioridade
{
	struct Feed *fila;
	int tamanho;
} TFilaPrioridade;
int TFilaPrioridade_Pai(int i);
void TFilaPrioridade_Inicia();
void TFilaPrioridade_Insere(int i, int identificacao, double grau_final, char **noticia);
int TFilaPrioridade_DesceHeap(int pai, int filho);
void TFilaPrioridade_SobeHeap(int i);
void TFilaPrioridade_Processar();

//TADFeed.h
typedef struct Feed
{
	int identificacao;
	double grau_final;
	char *noticia;
} TFeed;
void TFeed_Amigos_Inicia();
void TFeed_Processar_Entrada_Amigos();
void TFeed_Processar_Entrada_Feed();

//TADMemoria.h
char* TFeed_Noticia_Alocar();
TRaizAmigos* TArvoreAmigos_Raiz_Alocar();
TArvoreAmigos* TArvoreAmigos_Alocar();
TFeed* TFeed_Alocar();
TFilaPrioridade* TFilaPrioridade_Alocar();
TFeed* TFilaPrioridade_AlocarFila();
void TMemoria_Liberar();

int tam_feed, qtd_amigos, qtd_atualizacoes;
TFilaPrioridade *pArvore;
TArvoreAmigos *pArvoreAmigos;
int mem_texto = 100, mem_inteiros = 30, mem_fila = 4000, mem_raiz = 2, mem_feed = 2, mem_arvore = 600;

//TADMemória.c
char* TFeed_Noticia_Alocar()
{
	return (char*)malloc(sizeof(char) * mem_texto);
}

TRaizAmigos* TArvoreAmigos_Raiz_Alocar()
{
	return (TRaizAmigos*)malloc(sizeof(TRaizAmigos) * mem_raiz);
}

TArvoreAmigos* TArvoreAmigos_Alocar()
{
	TArvoreAmigos *novo = (TArvoreAmigos*)malloc(sizeof(TArvoreAmigos) * mem_arvore);
	novo->raiz = NULL;
	return novo;
}

TFeed* TFeed_Alocar()
{
	TFeed *novo = (TFeed*)malloc(sizeof(TFeed) * mem_feed);
	novo->noticia = TFeed_Noticia_Alocar();
	return novo;
}

TFilaPrioridade* TFilaPrioridade_Alocar()
{
	return (TFilaPrioridade*)malloc(sizeof(TFilaPrioridade) * mem_arvore);
}

TFeed* TFilaPrioridade_AlocarFila()
{
	return (TFeed*)malloc(sizeof(TFeed) * mem_fila);
}

void TMemoria_Liberar()
{
	free(pArvore);
}

//TADArvoreAmigos.c
void TAvoreAmigos_Inicia()
{
	pArvore = TFilaPrioridade_Alocar();
}

TRaizAmigos **temp;
void TArvoreAmigos_Pesquisar(TRaizAmigos **raiz, int identificacao)
{
	if ((*raiz) != NULL)
	{
		if (identificacao >= (*raiz)->identificacao)
		{
			TArvoreAmigos_Pesquisar(&(*raiz)->direita, identificacao);
		}
		else
		{
			TArvoreAmigos_Pesquisar(&(*raiz)->esquerda, identificacao);
		}
	}
	else
	{
		temp = raiz;
	}
}

void TArvoreAmigos_Buscar_Afinidade(TRaizAmigos **raiz, int identificacao)
{
	if ((*raiz) != NULL)
	{
		if (identificacao == (*raiz)->identificacao)
		{
			temp = raiz;
		}
		else if (identificacao >= (*raiz)->identificacao)
		{
			TArvoreAmigos_Buscar_Afinidade(&(*raiz)->direita, identificacao);
		}
		else
		{
			TArvoreAmigos_Buscar_Afinidade(&(*raiz)->esquerda, identificacao);
		}
	}
}

int x = 0;
void TArvoreAmigos_Inserir(TRaizAmigos **raiz, int identificacao, double grau)
{
	(*raiz) = TArvoreAmigos_Raiz_Alocar();
	(*raiz)->identificacao = identificacao;
	(*raiz)->grau = grau;
	(*raiz)->direita = NULL;
	(*raiz)->esquerda = NULL;
}

void TArvoreAmigos_Limpar(TRaizAmigos **raiz)
{
	if ((*raiz) != NULL)
	{
		TArvoreAmigos_Limpar(&(*raiz)->esquerda);
		TArvoreAmigos_Limpar(&(*raiz)->direita);
		free((*raiz));
	}
}

//TADFilaPrioridade.c
int TFilaPrioridade_Pai(int i){
	return (i / 2);
}

void TFilaPrioridade_Inicia()
{
	pArvore = TFilaPrioridade_Alocar();
	pArvore->tamanho = 0;
	pArvore->fila = TFilaPrioridade_AlocarFila();
}

void TFilaPrioridade_Insere(int i, int identificacao, double grau_final, char **noticia)
{
	if (pArvore->fila != NULL)
	{
		pArvore->fila[i].identificacao = identificacao;
		pArvore->fila[i].grau_final = grau_final;
		pArvore->fila[i].noticia = (*noticia);
		pArvore->tamanho++;
	}
}

int TFilaPrioridade_DesceHeap(int pai, int filho)
{
	//Auxiliares
	int aux_identificacao = pArvore->fila[pai].identificacao;
	double aux_grau_final = pArvore->fila[pai].grau_final;
	char *aux_noticia = pArvore->fila[pai].noticia;
	//Inverte
	pArvore->fila[pai].identificacao = pArvore->fila[filho].identificacao;
	pArvore->fila[pai].grau_final = pArvore->fila[filho].grau_final;
	pArvore->fila[pai].noticia = pArvore->fila[filho].noticia;
	//Volta o auxiliar
	pArvore->fila[filho].identificacao = aux_identificacao;
	pArvore->fila[filho].grau_final = aux_grau_final;
	pArvore->fila[filho].noticia = aux_noticia;
	return 1;
}

void TFilaPrioridade_SobeHeap(int i)
{
	if (i == 1){ return; }
	while (i > 1 && pArvore->fila[TFilaPrioridade_Pai(i)].grau_final < pArvore->fila[i].grau_final)
	{
		TFilaPrioridade_DesceHeap(TFilaPrioridade_Pai(i), i);
	}
	TFilaPrioridade_SobeHeap(i - 1);
}

void TFilaPrioridade_Processar()
{
	int i;
	//Construir Heap Máximo
	for (i = pArvore->tamanho; i > 1; i--)
	{
		TFilaPrioridade_SobeHeap(i);
		//Auxiliares
		int aux_identificacao = pArvore->fila[1].identificacao;
		double aux_grau_final = pArvore->fila[1].grau_final;
		char *aux_noticia = pArvore->fila[1].noticia;
		//Inverte
		pArvore->fila[1].identificacao = pArvore->fila[i].identificacao;
		pArvore->fila[1].grau_final = pArvore->fila[i].grau_final;
		pArvore->fila[1].noticia = pArvore->fila[i].noticia;
		//Volta o auxiliar
		pArvore->fila[i].identificacao = aux_identificacao;
		pArvore->fila[i].grau_final = aux_grau_final;
		pArvore->fila[i].noticia = aux_noticia;
	}

	while(tam_feed > 0 && qtd_atualizacoes > 0)
    {
        printf("%d%s\n", pArvore->fila[qtd_atualizacoes].identificacao, pArvore->fila[qtd_atualizacoes].noticia);
        tam_feed--;
        qtd_atualizacoes--;
    }
}

//TADFeed.c
void TFeed_Amigos_Inicia()
{
	pArvoreAmigos = TArvoreAmigos_Alocar();
}

void TFeed_Processar_Entrada_Amigos()
{
	int i;
	for (i = 0; i < qtd_amigos; i++)
	{
		int id;
		double grau;
		scanf("%d", &id);
		scanf("%lf", &grau);
		TArvoreAmigos_Pesquisar(&pArvoreAmigos->raiz, id);
		TArvoreAmigos_Inserir(&(*temp), id, grau*0.8);
	}
}

void TFeed_Processar_Entrada_Feed()
{
	int i;
	for (i = 1; i <= qtd_atualizacoes; i++)
	{
		int identificacao;
		double grau_final;
		char *noticia = TFeed_Noticia_Alocar();
		scanf("%d", &identificacao);
		scanf("%lf", &grau_final);
		gets(noticia);
		grau_final = grau_final * 0.2;
		TArvoreAmigos_Buscar_Afinidade(&pArvoreAmigos->raiz, identificacao);
		grau_final = grau_final + (*temp)->grau;
		TFilaPrioridade_Insere(i, identificacao, grau_final, &noticia);
	}
	TArvoreAmigos_Limpar(&pArvoreAmigos->raiz);
}

//Main.c
int main()
{
	scanf("%d %d %d", &tam_feed, &qtd_amigos, &qtd_atualizacoes);
	TFilaPrioridade_Inicia();
	TFeed_Amigos_Inicia();
	TFeed_Processar_Entrada_Amigos();
	TFeed_Processar_Entrada_Feed();
	TFilaPrioridade_Processar();
	TMemoria_Liberar();
	return 0;
}
