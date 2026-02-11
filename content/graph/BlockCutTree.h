/**
 * Description: Constructs the Block-Cut Tree, which is a bipartite graph with 
 * blocks (maximal 2-vertex-connected components) on one side and articulation 
 * points on the other. Works for disconnected graphs. Tree size is $\le 2N$. Be careful with self loops
 * and multi edges.
 * \texttt{art[i]}: number of new components created by removing $i$ (AP if $\ge 1$).
 * \texttt{blocks[i]}, \texttt{edgblocks[i]}: vertices/edges of block $i$.
 * \texttt{tree[i]}: the tree node index corresponding to block $i$.
 * \texttt{pos[i]}: the tree node index corresponding to vertex $i$.
 * Time: O(N + M)
 */
struct block_cut_tree {
	vector<vector<int>> g, blocks, tree;
	vector<vector<pair<int, int>>> edgblocks;
	stack<int> s;
	stack<pair<int, int>> s2;
	vector<int> id, art, pos;
	
	block_cut_tree(vector<vector<int>> g_) : g(g_) {
		int n = sz(g);
		id.resize(n, -1), art.resize(n), pos.resize(n);
		build();
	}

	int dfs(int i, int& t, int p = -1) {
		int lo = id[i] = t++;
		s.push(i);	
		
		if (p != -1) s2.emplace(i, p);
		for (int j : g[i]) 
            if (j != p and id[j] != -1) s2.emplace(i, j);
		
		for (int j : g[i]) if (j != p) {
			if (id[j] == -1) {
				int val = dfs(j, t, i);
				lo = min(lo, val);

				if (val >= id[i]) {
					art[i]++;
					blocks.emplace_back(1, i);
					while (blocks.back().back() != j) 
						blocks.back().push_back(s.top()), s.pop();

					edgblocks.emplace_back(1, s2.top()), s2.pop();
					while (edgblocks.back().back() != pii(j, i))
						edgblocks.back().push_back(s2.top()), s2.pop();
				}
			}
			else lo = min(lo, id[j]);
		}
		if (p == -1) {
            if(art[i]) art[i]--;
            else{
                blocks.emplace_back(1, i);
                edgblocks.emplace_back();
            }
        }
		return lo;
	}

	void build() {
		int t = 0;
	    rep(i, 0, sz(g)) if(id[i] == -1) dfs(i, t, -1);
		tree.resize(sz(blocks));
		rep(i, 0, sz(g)) if (art[i]) 
			pos[i] = sz(tree), tree.emplace_back();

		rep(i, 0, sz(blocks)) for (int j : blocks[i]) {
			if (!art[j]) pos[j] = i;
			else {
                tree[i].push_back(pos[j]);
                tree[pos[j]].push_back(i);
            }
		}
	}
};