/**
 * Usage: not A = \tilde A
 */

#pragma once

#include "SCC.h"

struct TwoSat{
	int n;
	SCC scc;
	vector<int> value;
	vector<pii> e;
	TwoSat(int n) : n(n){}
	bool solve(){
		value.resize(n);
		scc = SCC(2*n);
		for(auto &x : e) scc.add_edge(x.first, x.second); 
		scc.solve();
		for(int i=0; i<2*n; i++)
			if(scc.comp[i] == scc.comp[i^1]) return false;
		for(int i=0; i<n; i++)
			value[i] = scc.comp[id(i)] > scc.comp[id(~i)];
		return true;
	}
	void atMostOne(vector<int> &li){
		if(sz(li) <= 1) return;
		int cur = ~li[0];
		for(int i = 2; i < sz(li); i++) {
			int next = n++;
			addOr(cur, ~li[i]);
			addOr(cur, next);
			addOr(~li[i], next);
			cur = ~next;
		}
		addOr(cur, ~li[1]);
	}
	int id(int v) { return v < 0 ? (~v) * 2 ^ 1 : v * 2; }
	void add(int a, int b) { e.push_back({id(a), id(b)}); }
	void addOr(int a, int b) { add(~a, b); add(~b, a); }
	void addImp(int a, int b) { addOr(~a, b); }
	void addEqual(int a, int b){ addOr(a, ~b); addOr(~a, b); }
	void isFalse(int a) { addImp(a, ~a); }
};