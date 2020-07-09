#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef struct {
	int valor_vertice;
	int qtd_buraco;
} pPonte;

typedef struct {
	list<pPonte> adjacencia;
	int menor_qtd_buraco = -1;
} Visitantes;

pPonte New(int valor_v, int valor_b)
{
	pPonte temp;
	temp.valor_vertice = valor_v;
	temp.qtd_buraco = valor_b;
	return temp;
}

int menor_buraco = -1;
int n, m;
std::vector<Visitantes> grafo(0);

void Explorar(int indice, int n, int buraco)
{
	if ((grafo[indice].menor_qtd_buraco == -1 || buraco <= grafo[indice].menor_qtd_buraco) && indice != n)
	{
		for (std::list<pPonte>::iterator it = grafo[indice].adjacencia.begin(); it != grafo[indice].adjacencia.end(); it++)
		{
			grafo[indice].menor_qtd_buraco = buraco;
			Explorar(it->valor_vertice, n, it->qtd_buraco + buraco);
		}
	}

	if (indice == n)
	{
		if (menor_buraco == -1 || buraco < menor_buraco)
		{
			menor_buraco = buraco;
		}
	}
}

int main()
{
	cin >> n >> m;
	n++;
	grafo.resize(n + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v, p;
		cin >> u >> v >> p;
		if (u != v)
		{
			grafo[u].adjacencia.push_back(New(v, p));
		}
	}
	Explorar(0, n, 0);
	cout << menor_buraco;
	return 0;
}