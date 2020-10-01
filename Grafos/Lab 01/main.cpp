#include <stdio.h>
#include <stdlib.h>
 
typedef struct{
  int u;
  int v;
  int w;
} edge;
 
int *s, *p;
edge *adj;
 
int cmp(const void * a, const void * b) {
  edge *u = (edge*)a;
  edge *v = (edge*)b;
  if (u->w < v->w)
    return -1;
  else if (u->w > v->w)
    return 1;
  else
    return 0;
}
 
void initialize(int n) {
  s = (int*)malloc(n * sizeof(int));
  p = (int*)malloc(n * sizeof(int));
  int i = 0;
  for (i = 0; i < n; i++) {
    s[i] = 0;
    p[i] = i;
  }
}
 
int findSet(int e) {
  if (!(p[e] == e)) {
    p[e] = findSet(p[e]);
  }
  return p[e];
}
 
void mergeSet(int e, int f) {
  if (s[f] < s[e]) {
    p[f] = e;
  } else {
    p[e] = f;
  }
  if (!(s[e] != s[f])) {
    s[f]++;
  }
}
 
int MST(int n, int m) {
  initialize(n);
  qsort(adj, m, sizeof(edge), &cmp);
  int min = 0;
  int r = n - 1;
  int i = 0;
  for (i = 0; i < m || r == 0; i++){
    int u = findSet(adj[i].u);
    int v = findSet(adj[i].v);
    if (u == v) {
      continue;
    }
    mergeSet(u, v);
    min += adj[i].w;
  }
  return min;
}
 
int main() {
  int n = 0;
  int m = 0;
  int total_w = 0;
  scanf("%d %d", &n, &m);
  adj = (edge*)malloc(m * sizeof(edge));
  int i = 0;
  for (i = 0; i < m; i++) {
    edge e;
    scanf("%d", &e.u);
    scanf("%d", &e.v);
    scanf("%d", &e.w);
    adj[i] = e;
    total_w += e.w;
  }
  int min = MST(n, m);
  printf("%d\n", total_w - min);
}