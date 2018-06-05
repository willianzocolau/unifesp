#include <vector>
#include <iostream>

using namespace std;

int max(int x, int y) {
	if (x > y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

int mochila(int p, int n, vector<int> v, vector<int> t)
{
	vector<int> m;
	m.resize(p + 1);
	for (int i = 0; i <= p; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (t[j] <= i) {
				m[i] = max(m[i], m[i - t[j]] + v[j]);
			}
		}
	}
	return m[p];
}

int main()
{
	int p, n;
	cin >> p >> n;
	vector<int> t;
	t.resize(n + 1);
	vector<int> v;
	v.resize(n + 1);
	for (int i = 0; i < n; i++)
	{
		cin >> t[i] >> v[i];
	}
	cout << mochila(p, n, v, t);
	return 0;
}
