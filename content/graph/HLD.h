/**
 * Description: If values are stored on edges, set EDGE = true and store each edge's value
 * at the endpoint farther from the root (the deeper node).
 *
 * rp[i] is the representative (head) of the heavy path containing node i:
 * it is the node in that chain that is closest to the root.
 */

template<bool EDGE> struct HLD {
    int n, t;
    vector<vector<int>> g;
    vector<int> pai, rp, tam, pos, val, arr;
    Seg seg;
    HLD(int n, vector<vector<int>>& g, vector<int>& val) 
        : n(n), t(0), g(g), pai(n), rp(n), tam(n, 1),
             pos(n), val(val), arr(n) {
        calc_tam(0, -1);
        dfs(0, -1);
        seg.build(arr);
    }

    int calc_tam(int u, int p) {
        pai[u] = p;
        for (int& v : g[u]) {
            if (v == p) continue;
            tam[u] += calc_tam(v, u);
            if(tam[v] > tam[g[u][0]] || g[u][0] == p)
                swap(g[u][0], v);
        }
        return tam[u];
    }

    void dfs(int u, int p) {
        pos[u] = t++;
        arr[pos[u]] = val[u];
        for (int v : g[u]) {
            if (v == p) continue;
            rp[v] = (v == g[u][0] ? rp[u] : v);
            dfs(v, u);
        }
    }

    int query(int a, int b) { // query on the path from a to b
        int ans = 0; // neutral value
        while (rp[a] != rp[b]) {
            if (pos[a] < pos[b]) swap(a, b);
            ans = max(ans, seg.query(pos[rp[a]], pos[a]));
            a = pai[rp[a]];
        }
        if(pos[a] > pos[b]) swap(a, b);
        ans = max(ans, seg.query(pos[a] + EDGE, pos[b]));
        return ans;
    }

    void update(int a, int x) {
        seg.update(pos[a], x);
    }
};