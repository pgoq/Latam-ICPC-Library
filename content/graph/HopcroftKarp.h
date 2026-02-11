/**
 * Description: $ans$ is the size of the max matching. 
 * 
 * The match of x is $l[x]$
 *
 * Usage: HopcroftKarp(|X|, |Y|, edges(x, y))
 * Time: O(\sqrt{V}E)
 */
#pragma once
struct HopcroftKarp {
    vector<int> g, l, r;
    int ans;
    HopcroftKarp(int n, int m, vector<pii> e)
         : g(sz(e)), l(n, -1), r(m, -1), ans(0) {
        shuffle(all(e), rng);
        vector<int> deg(n + 1);
        for (auto& [x, y] : e) deg[x]++;
        rep(i, 1, n+1) deg[i] += deg[i - 1];
        for (auto& [x, y] : e) g[--deg[x]] = y;

        vector<int> q(n);
        while (true) {
            vector<int> a(n, -1), p(n, -1);
            int t = 0;
            rep(i, 0, n){
                if (l[i] == -1) {
                    q[t++] = a[i] = p[i] = i;
                }
            }
            bool match = false;
            rep(i, 0, t){
                int x = q[i];
                if (~l[a[x]]) continue;
                rep(j, deg[x], deg[x+1]) {
                    int y = g[j];
                    if (r[y] == -1) {
                        while (~y) {
                            r[y] = x;
                            swap(l[x], y);
                            x = p[x];
                        }
                        match = true, ans++;
                        break;
                    }
                    if (p[r[y]] == -1) {
                        q[t++] = y = r[y];
                        p[y] = x, a[y] = a[x];
                    }
                }
            }
            if (!match) break;
        }
    }
};