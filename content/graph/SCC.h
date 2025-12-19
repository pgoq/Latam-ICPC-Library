/**
 * Description: Kosaraju algorithm for calculating strongly connected components.
 * Components are ordered in topological order.
 */
#pragma once
struct SCC {
    int n, ncomp;
    vector<vector<int>> g, inv;
    vector<int> comp, vis, stk;
    SCC(){}
    SCC(int n) 
        : n(n),ncomp(0),g(n),inv(n),comp(n, -1),vis(n){}

    void dfs(int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs(v);
        stk.push_back(u);
    }
    void dfs_inv(int u) {
        comp[u] = ncomp;
        for (int v : inv[u]) {
            if (comp[v] == -1) dfs_inv(v);
        }
    }
    void solve() {
        for (int i = 0; i < n; i++) {
            if (!vis[i]) dfs(i);
        }
        reverse(all(stk));
        for (int u : stk) {
            if (comp[u] != -1) continue;
            dfs_inv(u);
            ncomp++;
        }
    }
    void add_edge(int a, int b) {
        g[a].push_back(b);
        inv[b].push_back(a);
    }
};