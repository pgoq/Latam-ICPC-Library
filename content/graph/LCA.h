/**
 * Description: LCA algorithm using binary lifting, $is\_ancestor(a, b)$ returns
 * true if $a$ is an ancestral of $b$ and false otherwise.
 * Time: O(N \log N)
 */
#pragma once

int tin[MAXN], tout[MAXN], timer=0;
int up[MAXN][BITS];
void dfs(int u, int p){
    tin[u] = timer++, up[u][0] = p;
    for (int i=1; i<BITS; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
    }
    for (int v: g[u]) if (v != p) dfs(v, u);
    tout[u] = timer;
}

bool is_ancestor(int u, int v){
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int lca(int u, int v){
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i=BITS-1; i>=0; i--) {
        if (up[u][i] && !is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}