#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> ilhas;
	ilhas.push_back(0);
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		ilhas.push_back(x);
	}

	int km_restante = 200;
	int parada = 0;
	for (int i = 0; i < n; i++)
	{
		int atual = ilhas[i];
		int proximo = ilhas[i + 1];
		int dif = proximo - atual;
		if (dif > km_restante)
		{
			parada++;
			km_restante = 200;
			i--;
		}
		else if(dif > 200)
		{
			parada = 0;
			break;
		}
		else
		{
			km_restante = km_restante - dif;
		}
	}
	cout << parada;
	return 0;
}