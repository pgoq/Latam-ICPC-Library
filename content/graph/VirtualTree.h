/**
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * virt[u] is the adjacency list of the virtual tree: it stores pairs
 * (v, dist), where v is a neighbor of u in the virtual tree and dist is the
 * distance between u and v in the original tree.
 * Time: $O(|S| \log |S|)$
 */
#pragma once

#include "LCA.h"

vector<pair<int, int>> virt[ms];

void build_virt(vector<int>& v) {
  auto cmp = [&](int i, int j){ return tin[i] < tin[j]; };
  sort(all(v), cmp);
  for (int i = 0, n = sz(v);i + 1 < n; i++) 
    v.push_back(lca(v[i], v[i + 1]));
  sort(all(v), cmp);
  v.erase(unique(all(v)), v.end());
  stack<int> st;
  for (auto u : v) {
    if (st.empty()) {
      st.push(u);
    }
    else {
      while(sz(st) && !is_ancestor(st.top(), u)) st.pop();
      int p = st.top();
      virt[p].emplace_back(u, abs(lvl[u] - lvl[p]));
      virt[u].emplace_back(p, abs(lvl[u] - lvl[p]));
      st.push(u);
    }
  }
}