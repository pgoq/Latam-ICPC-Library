
#pragma once
struct Bit {
  vector<int> bit;
  Bit(int n) : bit(n + 1) {}
  void update(int i, int v) {
    for (i++; i < sz(bit); i += i & -i) bit[i] += v;
  }
  int query(int i) {
    int ret = 0;
    for (i++; i > 0; i -= i & -i) ret += bit[i];
    return ret;
  }
};