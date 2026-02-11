/**
 * Description: Maintains bridges and 2-edge-connected components (2-ECC) incrementally.
 * \texttt{ds[0]} tracks Connected Components (CC).
 * \texttt{ds[1]} tracks 2-ECCs. Nodes $u, v$ are in the same 2-ECC iff \texttt{dsfind(u, 1) == dsfind(v, 1)}.
 * \texttt{g} stores the spanning forest edges (edges that were bridges when added).
 * An edge $(u, v) \in g$ is a current bridge iff \texttt{dsfind(u, 1) != dsfind(v, 1)}.
 * \texttt{bridges} tracks the total count of active bridges.
 * Use \texttt{init()} before starting.
 * Time: Amortized $O(\log N)$
 */
int bridges;
int ds[2][ms], sz[2][ms];
int h[ms], pai[ms], old[ms];
vector<int> g[ms];

void init() {
    bridges = 0;
    rep(i, 0, ms) {
        g[i].clear(), h[i] = 0;
        ds[0][i] = ds[1][i] = i;
        sz[0][i] = sz[1][i] = 1;
    }
}

int dsfind(int j, int i) {
    if(j == ds[i][j]) return ds[i][j];
    return ds[i][j] = dsfind(ds[i][j], i);
}

void dfs(int u, int p, int l) {
    h[u] = l;
    pai[u] = p;
    old[u] = dsfind(u, 1);
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u, l + 1);
    }
}

void updateNodes(int u, int p) {
    if (old[u] == old[p]) {
        ds[1][u] = ds[1][p];
    }
    else ds[1][u] = u;
    for (int v : g[u]) {
        if (v == p) continue;
        updateNodes(v, u);
    }
}

void mergeTrees(int a, int b) {
    bridges++;
    int iniA = a, iniB = b;
    a = dsfind(a, 0), b = dsfind(b, 0);
    if (sz[0][a] < sz[0][b]) swap(a, b), swap(iniA, iniB);
    dfs(iniB, iniA, h[iniA] + 1);
    old[iniA] = -1;
    updateNodes(iniB, iniA);
    ds[0][b] = a;
    sz[0][a] += sz[0][b];
}

void removeBridges(int a, int b) {
    a = dsfind(a, 1), b = dsfind(b, 1);
    while (a != b) {
        bridges--;
        if (h[a] < h[b]) swap(a, b);
        // ponte entre (a, pai[a]) deixou de existir
        ds[1][a] = dsfind(pai[a], 1);
        a = ds[1][a];
    }
}

void addEdge(int a, int b) {
    if (dsfind(a, 0) == dsfind(b, 0)) {
        removeBridges(a, b);
    }
    else {
        // nova ponte entre (a, b)
        g[a].push_back(b);
        g[b].push_back(a);
        mergeTrees(a, b);
    }
}