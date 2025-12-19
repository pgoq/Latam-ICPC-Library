/**
 * Description: Receives as input graph(node, edge index), number of edges and source. 
 * Returns list of {node, index of edge he came from}, if path/circuit does not exists
 * returns empty list.
 */
#pragma once
vector<pii> eulerPath(const vector<vector<pii>>& g, int nedges, int src) {
    int n = sz(g);
    vector<int> deg(n, 0), its(n, 0), used(nedges + 1, 0);
    vector<pii> s = { {src, -1} };
    //deg[src]++; //to allow paths, not only circuits
    vector<pii> ret;
    while (!s.empty()) {
        int u = s.back().first, &it = its[u];
        if (it == sz(g[u])) {
            ret.push_back(s.back());
            s.pop_back();
            continue;
        }
        auto& [nxt, id] = g[u][it++];
        if (!used[id]) {
            deg[u]--, deg[nxt]++;
            used[id] = 1;
            s.push_back({ nxt, id });
        }
    }
    for (int x : deg) {
        if (x < 0 || sz(ret) != (nedges + 1)) return {};
    }
    reverse(ret.begin(), ret.end());
    return ret;
}