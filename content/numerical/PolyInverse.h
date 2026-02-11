
#pragma once
vector<ll> get_inverse(vector<ll> a) {
  if (a.empty()) return {};
  int Y = sz(a) - 1, n = 32 - __builtin_clz(Y);
  n = (1 << n);
  a.resize(n);
  vector<ll> inv = { modpow(a[0], mod - 2) }, f, c;
  inv.reserve(n);
  for (int tam = 2; tam <= n; tam *= 2) {
    while (sz(f) < tam) f.push_back(a[sz(f)]);
    c = conv(f, inv);
    rep(i, 0, tam) c[i] = (c[i] == 0 ? 0 : mod - c[i]);
    c[0] += (c[0] + 2 >= mod ? 2 - mod : 2);
    inv = conv(inv, c);
    inv.resize(tam);
  }
  return inv;
}