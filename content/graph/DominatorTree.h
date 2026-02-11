/**
 * Description: Builds the Dominator Tree of a directed graph rooted at \texttt{root}.
 * Node $u$ dominates $v$ if every path from \texttt{root} to $v$ passes through $u$.
 * The immediate dominator of $v$ is the unique dominator closest to $v$ (excluding $v$).
 * Returns a vector \texttt{par} where \texttt{par[u]} is the parent of $u$ in the tree.
 * Roots and unreachable nodes satisfy \texttt{par[u] = u}.
 * Time: O(M \log N)
 */
struct dominator_tree {
	int n, t;
	vector<vector<int>> g, rg, bucket;
	vector<int> arr, par, rev, sdom, dom, ds, lbl;
	
	dominator_tree(int n) : n(n),t(0),g(n),rg(n),bucket(n),
   arr(n,-1),par(n),rev(n),sdom(n),dom(n),ds(n),lbl(n) {}
		
	void add_edge(int u, int v) { g[u].push_back(v); }

	void dfs(int u) {
		arr[u] = t;
		rev[t] = u;
		lbl[t] = sdom[t] = ds[t] = t;
    t++;
		for (int w : g[u]) {
			if (arr[w] == -1) {
				dfs(w);
				par[arr[w]] = arr[u];
			}
			rg[arr[w]].push_back(arr[u]);
		}
	}
	int find(int u, int x=0) {
		if (u == ds[u]) return x ? -1 : u;
		int v = find(ds[u], x+1);
		if (v < 0) return u;
		if(sdom[lbl[ds[u]]] < sdom[lbl[u]]) lbl[u]= lbl[ds[u]];
		ds[u] = v;
		return x ? v : lbl[u];
	}
	
	vector<int> run(int root) {
		dfs(root);
		iota(all(dom), 0);
		for (int i=t-1; i>=0; i--) {
			for(int w : rg[i]) sdom[i] = min(sdom[i],sdom[find(w)]);
			if (i) bucket[sdom[i]].push_back(i);
			for (int w : bucket[i]) {
				int v = find(w);
				if (sdom[v] == sdom[w]) dom[w] = sdom[w];
				else dom[w] = v;
			}
			if (i > 1) ds[i] = par[i];
		}
		rep(i, 1, t) {
			if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
		}
		vector<int> par(n);
		iota(all(par), 0);
		rep(i, 0, t) par[rev[i]] = rev[dom[i]];
		return par;
	}
};