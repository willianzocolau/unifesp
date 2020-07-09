#include <stdio.h>
#include <stdlib.h>

//TAD.h
typedef struct bloco {
	int indice;
	int valor;
	struct bloco *anterior;
	struct bloco *proximo;
} TBloco;

TBloco *pConjunto[100];
int n;

TBloco* AlocarBloco();
void Inicializar();
void Imprimir_Limpar();
TBloco* BuscarBloco(int valor);
TBloco *BuscarFim(TBloco *bloco);
void Organizar(TBloco *bloco);
void Move_Onto(int a, int b);
void Move_Over(int a, int b);
void Pile_Onto(int a, int b);
void Pile_Over(int a, int b);
void Processar();

//TAD.c
TBloco* AlocarBloco()
{
	return (TBloco*)malloc(sizeof(TBloco));
}

void Inicializar()
{
	int i;
	for (i = 0; i < n; i++)
	{
		pConjunto[i] = AlocarBloco();
		pConjunto[i]->indice = i;
		pConjunto[i]->valor = i;
		pConjunto[i]->proximo = NULL;
		pConjunto[i]->anterior = NULL;
	}
}

void Imprimir_Limpar()
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d:", i);
		if (pConjunto[i] != NULL)
		{
			TBloco *remover;
			while (pConjunto[i] != NULL)
			{
				remover = pConjunto[i];
				printf(" %d", pConjunto[i]->valor);
				pConjunto[i] = pConjunto[i]->proximo;
				free(remover);
			}
		}
		printf("\n");
	}
}

TBloco* BuscarBloco(int valor)
{
	TBloco *bloco = NULL;
	int i;
	for (i = 0; i < n; i++)
	{
		{
			if (pConjunto[i] != NULL)
			{
				bloco = pConjunto[i];
				while (bloco != NULL)
				{
					if (bloco->valor == valor)
					{
						return bloco;
					}
					bloco = bloco->proximo;
				}
			}
		}
	}
}

TBloco *BuscarFim(TBloco *bloco)
{
	while (bloco->proximo != NULL)
	{
		bloco = bloco->proximo;
	}
	return bloco;
}

void Organizar(TBloco *bloco)
{
	TBloco *verificar = bloco->proximo;
	TBloco *realocar = NULL;
	while (verificar != NULL)
	{
		realocar = verificar;
		verificar = verificar->proximo;
		if (realocar != NULL)
		{
			if (realocar->anterior != NULL)
			{
				realocar->anterior->proximo = NULL;
			}
			realocar->anterior = NULL;
			realocar->proximo = NULL;
			pConjunto[realocar->valor] = realocar;
			pConjunto[realocar->valor]->indice = realocar->valor;
		}
	}
	bloco->proximo = NULL;
}

//coloca o bloco a em cima do bloco b, retornando eventuais blocos que já estiverem sobre a ou b para as suas posições originais.
void Move_Onto(int a, int b)
{
	TBloco *bloco_a = NULL;
	TBloco *bloco_b = NULL;
	//Buscar bloco
	bloco_a = BuscarBloco(a);
	bloco_b = BuscarBloco(b);
	if (bloco_a->indice == bloco_b->indice){return;}
	//Organizar blocos que já estiverem sobre a ou b para as suas posições originais
	Organizar(bloco_a);
	Organizar(bloco_b);
	//Retirar bloco a da origem
	if (bloco_a->anterior != NULL)
	{
		bloco_a->anterior->proximo = NULL;
	}
	//Inserir em cima do bloco b
	bloco_b->proximo = bloco_a;
	bloco_a->anterior = bloco_b;
	bloco_a->indice = bloco_b->indice;
	pConjunto[a] = NULL;
}

//coloca o bloco a no topo do monte que contém bloco b, retornando eventuais blocos que já estiverem sobre a para as suas posições originais.
void Move_Over(int a, int b)
{
	TBloco *bloco_a = NULL;
	TBloco *bloco_b = NULL;
	//Buscar bloco
	bloco_a = BuscarBloco(a);
	bloco_b = BuscarBloco(b);
	if (bloco_a->indice == bloco_b->indice){return;}
	Organizar(bloco_a);
	//Retirar bloco a da origem
	if (bloco_a->anterior != NULL)
	{
		bloco_a->anterior->proximo = NULL;
	}
	//Inserir no topo do monte do bloco b
	bloco_b = BuscarFim(bloco_b);
	bloco_b->proximo = bloco_a;
	bloco_a->anterior = bloco_b;
	bloco_a->indice = bloco_b->indice;
	pConjunto[a] = NULL;
}

//coloca o bloco a, juntamente com todos os blocos que estiverem sobre ele, em cima do bloco b, retornando blocos sobre b para as suas posições originais.
void Pile_Onto(int a, int b)
{
	TBloco *bloco_a = NULL;
	TBloco *bloco_b = NULL;
	TBloco *aux = NULL;
	//Buscar bloco
	bloco_a = BuscarBloco(a);
	bloco_b = BuscarBloco(b);
	if (bloco_a->indice == bloco_b->indice){return;}
	//Organizar blocos que já estiverem sobre b para as suas posições originais
	Organizar(bloco_b);
	//Retirar bloco a da origem
	if (bloco_a->anterior != NULL)
	{
		bloco_a->anterior->proximo = NULL;
	}
	//Inserir em cima do bloco b
	bloco_b->proximo = bloco_a;
	bloco_a->anterior = bloco_b;
	aux = bloco_a;
	while (aux != NULL)
	{
		aux->indice = bloco_b->indice;
		aux = aux->proximo;
	}
	pConjunto[a] = NULL;
}

//coloca o bloco a, juntamente com todos os blocos que estiverem sobre ele, no topo do monte que contém bloco b.
void Pile_Over(int a, int b)
{
	TBloco *bloco_a = NULL;
	TBloco *bloco_b = NULL;
	TBloco *aux = NULL;
	//Buscar bloco
	bloco_a = BuscarBloco(a);
	bloco_b = BuscarBloco(b);
	if (bloco_a->indice == bloco_b->indice){return;}
	//Retirar bloco a da origem
	if (bloco_a->anterior != NULL)
	{
		bloco_a->anterior->proximo = NULL;
	}
	//Inserir no topo do monte do bloco b
	bloco_b = BuscarFim(bloco_b);
	bloco_b->proximo = bloco_a;
	bloco_a->anterior = bloco_b;
	aux = bloco_a;
	while (aux != NULL)
	{
		aux->indice = bloco_b->indice;
		aux = aux->proximo;
	}
	pConjunto[a] = NULL;
}

void Processar()
{
	char a_1[4], b_1[4];
	int a_2, b_2;
	scanf("%s", a_1);
	while (a_1[0] != 'q')
	{
		scanf("%d %s %d", &a_2, b_1, &b_2);
		if (a_2 != b_2)
		{
			if (a_1[0] == 'm' && b_1[1] == 'n')
			{
				Move_Onto(a_2, b_2);
			}
			else if (a_1[0] == 'm' && b_1[1] == 'v')
			{
				Move_Over(a_2, b_2);
			}
			else if (a_1[0] == 'p' && b_1[1] == 'n')
			{
				Pile_Onto(a_2, b_2);
			}
			else if (a_1[0] == 'p' && b_1[1] == 'v')
			{
				Pile_Over(a_2, b_2);
			}
		}
		scanf("%s", a_1);
	}

}

//Main.c
int main()
{
	scanf("%d", &n);
	Inicializar();
	Processar();
	Imprimir_Limpar();
	return 0;
}
