#pragma once
vector<int> g[ms];
int low[ms], tin[ms], vis[ms], t;

void dfs(int u = 0, int p = -1) {
    vis[u] = true;
    low[u] = tin[u] = t++;
    for (auto v : g[u]) {
        if (v == p) continue;
        if (vis[v]) {
            low[u] = min(low[u], tin[v]);
        }
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            // if (low[v] >= tin[u] && p != -1), U is an articulation point
            if (low[v] > tin[u]) { 
                // edge from U to V is a bridge
            }
            // children++
        }
    }
    // if(children > 1 && p == -1) root is an articulation point
}