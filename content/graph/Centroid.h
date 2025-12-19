/**
 * Description: Call decomp(0) to solve, marked array should be initially set to zero.
 * Time: O(N \log N)
 */
#pragma once
int tam[ms], marked[ms];

int calc_tam(int u, int p) {
  tam[u] = 1;
  for (int v : g[u]) {
    if (v != p && !marked[v]) tam[u] += calc_tam(v, u);
  }
  return tam[u];
}

int get_centroid(int u, int p, int tot) {
  for (int v : g[u]) {
    if (v != p && !marked[v] && (tam[v] > (tot / 2))) 
      return get_centroid(v, u, tot);
  }
  return u;
}
// Cent is a child of P in the centroid tree
void decomp(int u, int p = -1) {
  calc_tam(u, -1);
  int cent = get_centroid(u, -1, tam[u]);
  marked[cent] = 1;
  for (int v : g[cent]) {
    if (!marked[v]) decomp(v, cent);
  }
}
