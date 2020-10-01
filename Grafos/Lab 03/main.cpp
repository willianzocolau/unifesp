#include <iostream>
#include <list>
#include <queue>
#include <tr1/unordered_map>

typedef std::pair<int, int> edge;

int even(int x)
{
    return x * 10 + 2;
}

int odd(int x)
{
    return x * 10 + 1;
}

void add_edge(std::list<edge> *adj, int u, int v, int w)
{
    adj[even(u)].push_back({ odd(v), w });
    adj[odd(u)].push_back({ even(v), w });
    adj[odd(v)].push_back({ even(u), w });
    adj[even(v)].push_back({ odd(u), w });
}

std::tr1::unordered_map<int, int> dijkstra(std::list<edge> *adj, int src, int target, int n)
{
	std::priority_queue<edge, std::vector <edge>, std::greater<edge> > q;
    std::tr1::unordered_map<int, int> dist;
	q.push({ 0, src });
	dist[src] = 0;
	while (!q.empty())
	{
		int u = q.top().second;
		q.pop();
		for (std::list<edge>::iterator i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = (*i).first;
			int weight = (*i).second;
			if ((dist[v] > dist[u] + weight) || (v != src && dist[v] == 0))
			{
				dist[v] = dist[u] + weight;
				q.push({ dist[v], v });
                // if(v == target)
                //     return dist;
			}
		}
	}
    return dist;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::list<edge> *adj = new std::list<edge>[n*10+2];
    for(int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
    	add_edge(adj, u-1, v-1, w);
    }

    std::tr1::unordered_map<int, int> dist = dijkstra(adj, even(0), even(n-1), n);

    if (n == 2 || dist[even(n-1)] == 0)
    	std::cout << -1 << std::endl;
    else
	    std::cout << dist[even(n-1)] << std::endl;

	return 0;
}
