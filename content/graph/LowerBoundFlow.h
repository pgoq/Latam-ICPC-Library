/**
 * Description: Calculates maximum flow with lower/upper bounds on edges.
 * Returns -1 if no feasible flow exists.
 * \texttt{add(a, b, l, r)} adds edge $a \to b$ where flow $f$ must satisfy $l \le f \le r$.
 * \texttt{add(a, b, c)} adds edge $a \to b$ with capacity $c$ (implies $0 \le f \le c$).
 * Same complexity as Dinic.
 */
#include "Dinic.h"

struct lb_max_flow : Dinic {
	vector<ll> d;
	lb_max_flow(int n) : Dinic(n + 2), d(n, 0) {}
	void add(int a, int b, int l, int r) {
		d[a] -= l;
		d[b] += l;
		Dinic::add(a, b, r - l);
	}
	void add(int a, int b, int c) {
		Dinic::add(a, b, c);
	}
	bool has_circulation() {
		int n = sz(d);
		ll cost = 0;
		rep(i, 0, n){
			if (d[i] > 0) {
				cost += d[i];
				Dinic::add(n, i, d[i]);
			} else if (d[i] < 0) {
				Dinic::add(i, n+1, -d[i]);
			}
		}

		return (Dinic::maxFlow(n, n+1) == cost);
	}
	bool has_flow(int src, int snk) {
		Dinic::add(snk, src, INF);
		return has_circulation();
	}
	ll max_flow(int src, int snk) {
		if (!has_flow(src, snk)) return -1;
		Dinic::F = 0;
		return Dinic::maxFlow(src, snk);
	}
};
