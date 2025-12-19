/**
 * Description: $lcp[i]$ is the length of the longest common prefix between the suffixes
 * $s[sa[i]..n-1]$ and $s[sa[i-1]..n-1]$.
 * 
 * If we concatenate multiple strings using separator characters, the
 * separator that appears furthest to the right must be the smallest
 * character in the alphabet.
 */

#pragma once
struct SuffixArray {
	vector<int> sa, lcp;
	SuffixArray(string s, int lim=256) {
		s.push_back('$'); 
		int n = sz(s), k = 0, a, b;
		vector<int> x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for(int j = 0, p = 0; p < n; j= max(1, j*2), lim = p) {
			p = j, iota(all(y), n - j);
			for(int i=0; i<n; i++){
				if (sa[i] >= j) y[p++] = sa[i] - j;
			}
			fill(all(ws), 0);
			for(int i=0; i<n; i++) ws[x[i]]++;
			for(int i=1; i<lim; i++) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			for(int i=1; i<n; i++){
				a = sa[i - 1], b = sa[i];
				x[b] = p-1;
				if(y[a] != y[b] || y[a+j] != y[b+j]) x[b] = p++;
			}
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
		sa = vector<int>(sa.begin() + 1, sa.end());
		lcp = vector<int>(lcp.begin() + 1, lcp.end());
	}
};