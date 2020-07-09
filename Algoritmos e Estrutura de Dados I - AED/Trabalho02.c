#include <stdio.h>
#include <stdlib.h>

//TAD.h
typedef struct Caixa
{
	int indice;
	int tempo_atendimento;
	int vazio;
	struct Caixa *proximo;
	struct Caixa *anterior;
} TCaixa;

typedef struct Banco
{
	int qtd_caixas;
	int qtd_atendimentos;
	struct Caixa *inicio;
	struct Caixa *fim;
} TBanco;

typedef struct Cliente
{
	int indice;
	int chegada;
	int atendimento;
	struct Cliente *proximo;
	struct Cliente *anterior;
}TCliente;

typedef struct Fila
{
	int qtd_clientes;
	int qtd_tempor_maior;
	struct Cliente *inicio;
	struct Cliente *fim;
}TFila;

TCaixa* AlocarCaixa();
TCliente* AlocarCliente();
TBanco* AlocarBanco();
TFila* AlocarFila();
void Inicializar();
void InicializarCaixasBanco();
void InserirClienteFila(int chegada, int atendimento);
void Processar();
void lerDados();
void Imprimir();
void Liberar();

//TAD.c
TBanco *pBanco = NULL;
TFila *pFila = NULL;

TCaixa* AlocarCaixa()
{
	TCaixa *novo = (TCaixa*)malloc(sizeof(TCaixa));
	novo->vazio = 1;
	novo->tempo_atendimento = 0;
	return novo;
}

TCliente* AlocarCliente()
{
	return (TCliente*)malloc(sizeof(TCliente));
}

TBanco* AlocarBanco()
{
	TBanco *pNovo = (TBanco*)malloc(sizeof(TBanco));
	pNovo->inicio = AlocarCaixa();
	pNovo->inicio->indice = -1;
	pNovo->fim = pNovo->inicio;
	pNovo->qtd_caixas = 0;
	pNovo->qtd_atendimentos = 0;
	return pNovo;
}

TFila* AlocarFila()
{
	TFila *pNovo = (TFila*)malloc(sizeof(TFila));
	pNovo->inicio = AlocarCliente();
	pNovo->inicio->indice = -1;
	pNovo->fim = pNovo->inicio;
	pNovo->qtd_clientes = 0;
	pNovo->qtd_tempor_maior = 0;
	return pNovo;
}

void Inicializar()
{
	pBanco = AlocarBanco();
	pFila = AlocarFila();
}

void InicializarCaixasBanco()
{
	int i;
	for (i = 0; i < pBanco->qtd_caixas; i++)
	{
		TCaixa *novo = AlocarCaixa();
		novo->indice = i;
		novo->proximo = pBanco->inicio;
		novo->anterior = pBanco->fim;
		pBanco->fim->proximo = novo;
		pBanco->fim = novo;
	}
}

void InserirClienteFila(int chegada, int atendimento)
{
	TCliente *novo = AlocarCliente();
	novo->indice = pFila->fim->indice + 1;
	novo->chegada = chegada;
	novo->atendimento = atendimento;
	novo->proximo = pFila->inicio;
	novo->anterior = pFila->fim;
	pFila->fim->proximo = novo;
	pFila->fim = novo;
	pFila->qtd_clientes++;
}

void Processar()
{
	int i;
	TCaixa *caixa = pBanco->inicio->proximo;
	for (i = 0; i < pBanco->qtd_atendimentos; i++)
	{
		if (caixa->vazio == 1)
		{
			caixa->tempo_atendimento = pFila->inicio->proximo->atendimento;
			caixa->vazio = 0;
			if (caixa->proximo->indice == -1)
			{
				caixa = pBanco->inicio->proximo;
			}
			else
			{
				caixa = caixa->proximo;
			}
		}
		else
		{
			int x;
			caixa = pBanco->inicio;
			TCaixa *menor_caixa = caixa->proximo;
			for (x = 0; x < pBanco->qtd_caixas; x++)
			{
				caixa = caixa->proximo;
				if ((caixa->tempo_atendimento - pFila->inicio->proximo->chegada) < (menor_caixa->tempo_atendimento - pFila->inicio->proximo->chegada))
				{
					menor_caixa = caixa;
				}
			}

			if ((menor_caixa->tempo_atendimento - pFila->inicio->proximo->chegada) > 20)
			{
				pFila->qtd_tempor_maior++;
			}
			menor_caixa->tempo_atendimento = menor_caixa->tempo_atendimento + pFila->inicio->proximo->atendimento;
		}

		TCliente *remover = pFila->inicio->proximo;
		pFila->inicio->proximo = pFila->inicio->proximo->proximo;
		free(remover);
	}
}

void lerDados()
{
	scanf("%d %d", &pBanco->qtd_caixas, &pBanco->qtd_atendimentos);
	InicializarCaixasBanco();
	int i, chegada, atendimento;
	for (i = 0; i < pBanco->qtd_atendimentos; i++)
	{

		scanf("%d %d", &chegada, &atendimento);
		InserirClienteFila(chegada, atendimento);
	}
}

void Imprimir()
{
	printf("%d", pFila->qtd_tempor_maior);
}

void Liberar()
{
	int i;
	TCaixa *remover;
	for (i = 0; i < pBanco->qtd_caixas; i++)
	{
		remover = pBanco->inicio->proximo;
		pBanco->inicio->proximo = pBanco->inicio->proximo->proximo;
		free(remover);
	}
	free(pBanco->inicio);
	free(pBanco);
}

int main()
{
	Inicializar();
	lerDados();
	Processar();
	Imprimir();
	Liberar();
	return 0;
}
