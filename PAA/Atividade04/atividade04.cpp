#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stack>

using namespace std;

int main()
{
	//N - Número de pessoas
	//P - Relações
	//K - Número mínimo de amigos
	int n, p, k;
	cin >> n >> p >> k;
	int **matrix = (int **)malloc((n+1) * sizeof(int *));
	for (int i = 0; i < n + 1; i++)
		matrix[i] = (int *)malloc((n+1) * sizeof(int));
	map<int, int> r;
	stack<int> e;
	for (int i = 0; i < p; i++)
	{
		int a, b;
		cin >> a >> b;
		matrix[a][b] = 1;
		matrix[b][a] = 1;
		if (r.find(a) == r.end())
			r[a] = 0;
		if (r.find(b) == r.end())
			r[b] = 0;
		r[a]++;
		r[b]++;
	}
	bool f;
	do {
		f = false;
		for (typename map<int, int>::iterator it = r.begin(); it != r.end(); ++it) {
			if (it->second < k)
			{
				for (int i = 1; i < n + 1; i++)
				{
					if (matrix[i][it->first] == 1)
					{
						matrix[i][it->first] = 0;
						r[i]--;
					}
				}
				e.push(it->first);
				f = true;
			}
		}

		while (e.size() > 0)
		{
			r.erase(e.top());
			e.pop();
		}
	} while (f == true);
	cout << r.size() << endl;
	return 0;
}