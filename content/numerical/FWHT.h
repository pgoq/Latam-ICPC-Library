/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

void FST(vector<ll>& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) {
      for (int j = i; j < i + step; j++) {
        ll& u = a[j], &v = a[j + step];
        tie(u, v) =
        inv ? pair(v - u, u) : pair(v, u + v); // AND
        // inv ? pair(v, u - v) : pair(u + v, u); // OR /// include-line
        // pair(u + v, u - v);  // XOR /// include-line
      }
    }
  }
  // if(inv) for(ll& x : a) x /= sz(a); // XOR only /// include-line
}
vector<ll> conv(vector<ll> a, vector<ll> b) {
  FST(a, 0); FST(b, 0);
  for (int i = 0; i < sz(a); i++) a[i]*=b[i];
  FST(a, 1); return a;
}