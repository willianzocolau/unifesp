#include <stdio.h>
#include <stdlib.h>

//TAD.h
typedef struct Carta
{
	int carta;
	int naipe;
	int validada;
	struct Carta *proximo;
	struct Carta *anterior;
} TCarta;

typedef struct Jogo
{
	int qtd_cartas;
	struct Carta *inicio;
	struct Carta *fim;
} TJogo;

TJogo *AlocarJogo();
TCarta* AlocarCarta();
void Inicializar();
int GetGrandezaNaipe(char naipe);
int GetMaiorCarta(TCarta *pCarta, TCarta *pMaior);
int GetProximoJogador(int ultimo, int *sentido_jogo);
void GetRegrasCartaDescarte(int *qtd_cartas, int *sn_perde_vez);
void InserirDescarte(int carta, int naipe);
TCarta* RemoverBaralho();
TCarta* RemoverJogador(int jogador);
void Processar();
void lerDados();
void Liberar();

//TAD.c
int n_jogadores, n_cartas_jogadores, tam_baralho, indice_baralho;
TJogo *pJogador = NULL;
TJogo *pBaralho = NULL;
TCarta *pDescarte = NULL;

TJogo *AlocarJogo()
{
	return (TJogo*)malloc(sizeof(TJogo) * 10);
}

TCarta* AlocarCarta()
{
	return (TCarta*)malloc(sizeof(TCarta));
}

void Inicializar()
{
	pJogador = AlocarJogo();
	pBaralho = AlocarJogo();
	pDescarte = AlocarCarta();
}

int GetGrandezaNaipe(char naipe)
{
	if ((naipe == 'c') || (naipe == 'C')){ return 1; }
	else if ((naipe == 'd') || (naipe == 'D')){ return 2; }
	else if ((naipe == 'h') || (naipe == 'H')){ return 3; }
	else if ((naipe == 's') || (naipe == 'S')){ return 4; }
	else { return 0; }
}

int GetMaiorCarta(TCarta *pCarta, TCarta *pMaior)
{
	if (pCarta->carta > pMaior->carta)
	{
		return 1;
	}
	else if (pCarta->carta == pMaior->carta)
	{
		if (pCarta->naipe > pMaior->naipe)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else{ return 0; }
}

int GetProximoJogador(int ultimo, int *sentido_jogo)
{
	int proximo = ultimo;
	if (pDescarte->validada == 1 && n_jogadores > 2)//Carta validada, rodada segue normalmente
	{
		if (*sentido_jogo == 1)
		{
			if (((ultimo + 1) - n_jogadores) == 0)
			{
				proximo = 0;
			}
			else
			{
				proximo++;
			}
		}
		else if (*sentido_jogo == 2)
		{
			if (((ultimo - 1)) == -1)
			{
				proximo = (n_jogadores - 1);
			}
			else
			{
				proximo--;
			}
		}
	}
	else if (*sentido_jogo == 1 && n_jogadores > 2 && pDescarte->validada == 0)//Horário
	{
		if (pDescarte->carta == 12)//Dama - Inverte o sentido;
		{
			if (ultimo == 0)
			{
				proximo = (n_jogadores - 1);
			}
			else
			{
				proximo--;
			}
			*sentido_jogo = 2;
		}
		else
		{
			if (((ultimo + 1) - n_jogadores) == 0)
			{
				proximo = 0;
			}
			else
			{
				proximo++;
			}
		}
	}
	else if (*sentido_jogo == 2 && n_jogadores > 2 && pDescarte->validada == 0)//Anti-horário
	{
		if (pDescarte->carta == 12)//Dama - Inverte o sentido;
		{
			if (((ultimo + 1) - n_jogadores) == 0)
			{
				proximo = 0;
			}
			else
			{
				proximo++;
			}
			*sentido_jogo = 1;
		}
		else
		{
			if (((ultimo - 1)) == -1)
			{
				proximo = (n_jogadores - 1);
			}
			else
			{
				proximo--;
			}
		}
	}
	else if (n_jogadores == 2)
	{
		if (((ultimo + 1) - n_jogadores) == 0)
		{
			proximo = 0;
		}
		else
		{
			proximo++;
		}
	}

	return proximo;
}

void GetRegrasCartaDescarte(int *qtd_cartas, int *sn_perde_vez)
{
	*qtd_cartas = -1;
	*sn_perde_vez = -1;
	if (pDescarte->validada == 0)
	{
		if (pDescarte->carta == 1)//Ás - Sacar uma cartas e perde a vez;
		{
			*qtd_cartas = 1;
			*sn_perde_vez = 1;
			pDescarte->validada = 1;
		}
		else if (pDescarte->carta == 7)//Sete - Sacar duas cartas e perde a vez
		{
			*qtd_cartas = 2;
			*sn_perde_vez = 1;
			pDescarte->validada = 1;
		}
		else if (pDescarte->carta == 11)//Valete - perde a vez
		{
			*sn_perde_vez = 1;
			pDescarte->validada = 1;
		}
	}
}

void InserirDescarte(int carta, int naipe)
{
	pDescarte->carta = carta;
	pDescarte->naipe = naipe;
	pDescarte->validada = 0;
}

void Inserir(int jogador, int carta, int naipe, TJogo *pDados)
{
	TCarta *nova = AlocarCarta();
	nova->anterior = pDados[jogador].fim;
	nova->carta = carta;
	nova->naipe = naipe;
	pDados[jogador].fim->proximo = nova;
	pDados[jogador].fim = nova;
	if (carta != -1 && naipe != -1)
	{
		pDados[jogador].qtd_cartas++;
	}
	nova = NULL;
	free(nova);
}

TCarta* RemoverBaralho()
{
	TCarta *pCarta = AlocarCarta();
	if (pBaralho[0].qtd_cartas == 0)
	{
		pCarta->carta = -1;
		pCarta->naipe = -1;
		return pCarta;
	}

	pCarta = pBaralho[0].inicio->proximo;
	if (pCarta->proximo == pBaralho[0].fim)
	{
		pBaralho[0].inicio->proximo = pCarta->proximo;
		pBaralho[0].fim = pCarta->proximo;
	}
	else if (pBaralho[0].inicio->proximo == pBaralho[0].fim)
	{
		pBaralho[0].fim = pBaralho[0].inicio;
	}
	else
	{
		pCarta->proximo->anterior = pBaralho[0].inicio;
		pBaralho[0].inicio->proximo = pCarta->proximo;
	}
	pBaralho[0].qtd_cartas--;
	return pCarta;
}

TCarta* RemoverJogador(int jogador)
{
	int tem_carta = 0, i, qtd;
	TCarta *pMaior = AlocarCarta();
	TCarta *pDireita = AlocarCarta();
	TCarta *pEsquerda = AlocarCarta();
	pMaior->carta = -1;
	pMaior->naipe = -1;
	pDireita = pJogador[jogador].inicio->proximo;
	pEsquerda = pJogador[jogador].fim;
	if ((pJogador[jogador].qtd_cartas % 2) == 0)
	{
		qtd = (pJogador[jogador].qtd_cartas / 2);
	}
	else
	{
		qtd = (pJogador[jogador].qtd_cartas / 2);
		qtd++;
	}
	for (i = 0; i < qtd; i++)
	{
		if ((pDireita->carta == pDescarte->carta || pDireita->naipe == pDescarte->naipe) &&
			GetMaiorCarta(pDireita, pMaior)
			)
		{
			pMaior = pDireita;
			tem_carta = 1;
		}

		if ((pEsquerda->carta == pDescarte->carta || pEsquerda->naipe == pDescarte->naipe) &&
			GetMaiorCarta(pEsquerda, pMaior)
			)
		{
			pMaior = pEsquerda;
			tem_carta = 1;
		}

		pDireita = pDireita->proximo;
		pEsquerda = pEsquerda->anterior;
	}

	if (tem_carta)
	{
		if (pJogador[jogador].inicio->proximo == pJogador[jogador].fim)
		{
			pJogador[jogador].fim = pJogador[jogador].inicio;
		}
		else if (pJogador[jogador].inicio->proximo == pMaior)
		{
			pMaior->proximo->anterior = pJogador[jogador].inicio;
			pJogador[jogador].inicio->proximo = pMaior->proximo;
		}
		else if (pJogador[jogador].fim == pMaior)
		{
			pMaior->proximo = NULL;
			pJogador[jogador].fim = pMaior->anterior;
		}
		else
		{
			pEsquerda = pMaior->anterior;
			pDireita = pMaior->proximo;
			pEsquerda->proximo = pDireita;
			pDireita->anterior = pEsquerda;
		}
		pJogador[jogador].qtd_cartas--;
	}
	else
	{
		pMaior->carta = -1;
		pMaior->naipe = -1;
	}
	return pMaior;
}

void Processar()
{
	int jogador = 0, proximo_jogador = 0, qtd_cartas = -1, sn_perde_vez = -1, sentido = 1, rodada = 0;
	TCarta *pCarta;
	GetProximoJogador(jogador, &sentido);
	while (pJogador[jogador].qtd_cartas != 0)
	{
		jogador = proximo_jogador;
		GetRegrasCartaDescarte(&qtd_cartas, &sn_perde_vez);
		if (qtd_cartas > 0)
		{
			int i = 0;
			for (i = 0; i < qtd_cartas; i++)
			{
				pCarta = RemoverBaralho();
				Inserir(jogador, pCarta->carta, pCarta->naipe, pJogador);
				free(pCarta);
			}
			pDescarte->validada = 1;
		}
		else if (sn_perde_vez == 1)
		{
			pDescarte->validada = 1;
		}
		else
		{
			pCarta = RemoverJogador(jogador);
			if (pCarta->carta == -1 && pCarta->naipe == -1)
			{
				pCarta = RemoverBaralho();
				if ((pCarta->carta == pDescarte->carta || pCarta->naipe == pDescarte->naipe))
				{
					InserirDescarte(pCarta->carta, pCarta->naipe);
				}
				else
				{
					Inserir(jogador, pCarta->carta, pCarta->naipe, pJogador);
					pDescarte->validada = 1;
				}
			}
			else
			{
				InserirDescarte(pCarta->carta, pCarta->naipe);
			}
			free(pCarta);
		}
		proximo_jogador = GetProximoJogador(jogador, &sentido);
		rodada++;
	}
	printf("%d", jogador + 1);
}

void lerDados()
{
	int x = 0, y = 0, carta = 0, qtd_baralho = tam_baralho - ((n_jogadores*n_cartas_jogadores) + 1);
	char naipe;
	for (x = 0; x < n_jogadores; x++)
	{
		TCarta *cabeca = (TCarta*)malloc(sizeof(TCarta));
		cabeca->carta = -1;
		cabeca->naipe = -1;
		pJogador[x].qtd_cartas = 0;
		pJogador[x].inicio = cabeca;
		pJogador[x].fim = cabeca;
		for (y = 0; y < n_cartas_jogadores; y++)
		{
			scanf("%d %c", &carta, &naipe);
			Inserir(x, carta, GetGrandezaNaipe(naipe), pJogador);
		}
		cabeca = NULL;
		free(cabeca);
	}

	scanf("%d %c", &carta, &naipe);
	InserirDescarte(carta, GetGrandezaNaipe(naipe));

	TCarta *cabeca = (TCarta*)malloc(sizeof(TCarta));
	cabeca->carta = -1;
	cabeca->naipe = -1;
	pBaralho[0].qtd_cartas = 0;
	pBaralho[0].inicio = cabeca;
	pBaralho[0].fim = cabeca;
	cabeca = NULL;
	free(cabeca);
	for (x = 0; x < qtd_baralho; x++)
	{
		scanf("%d %c", &carta, &naipe);
		Inserir(0, carta, GetGrandezaNaipe(naipe), pBaralho);
	}
	cabeca = NULL;
	free(cabeca);
}

void Liberar()
{
	free(pDescarte);
	TCarta *c = NULL;
	int x, y;
	for (x = 0; x < n_jogadores; x++)
	{
		if (pJogador[x].qtd_cartas > 0)
		{
			for (y = 0; y < pJogador[x].qtd_cartas; y++)
			{
				c = pJogador[x].fim;
				pJogador[x].fim = pJogador[x].fim->anterior;
				free(c);
			}
		}
	}

	if (pBaralho[0].qtd_cartas > 0)
	{
		for (y = 0; y < pBaralho[x].qtd_cartas; y++)
		{
			c = pBaralho[x].fim;
			pBaralho[x].fim = pBaralho[x].fim->anterior;
			free(c);
		}
	}
}

int main()
{
	Inicializar();
	scanf("%d %d %d", &n_jogadores, &n_cartas_jogadores, &tam_baralho);
	lerDados();
	Processar();
	Liberar();
	return 0;
}
