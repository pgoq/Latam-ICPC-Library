/**
 * Time:
 * - $O(\min(m \cdot \text{max\_flow},\; n^{2} m))$.
 * 
 * - For graphs with unit capacities: $O(\min(m \sqrt{m},\; m n^{2/3}))$.
 * 
 * - If every vertex has in-degree $1$ or out-degree $1$: $O(m \sqrt{n})$.
 * 
 * - With capacity scaling: $O(n m \log(\text{MAXCAP}))$ with high constant factor.
 * 
 */
#pragma once
struct Dinic {
	const bool scaling = false;
	int lim;         
	struct edge {
		int to, rev;
		ll cap, flow;
		bool res;
		edge(int to_, ll cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_){}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	Dinic(int n) : g(n), lev(n), beg(n), F(0) {}

	void add(int a, int b, ll c, ll other = 0) {
		g[a].emplace_back(b, c, sz(g[b]), false);
		g[b].emplace_back(a, other, sz(g[a])-1, true);
	}
	bool bfs(int s, int t) {
		fill(all(lev), -1);
		fill(all(beg), 0);
        lev[s] = 0;
		queue<int> q; q.push(s);
		while (sz(q)) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	ll dfs(int v, int s, ll f = INF) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < sz(g[v]); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			ll foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll maxFlow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (ll ff = dfs(s, t)) F += ff;
		return F;
	}
    bool inCut(int u){ return lev[u] != -1; }
};
