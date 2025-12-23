/**
 * Description: $lower\_bound$ works the same as on vectors
 * Time: O(\log N)
 */
#pragma once
struct Bit {
  vector<ll> bit;
  Bit(int n) : bit(n + 1) {}
  void update(int i, ll v) {
    for (i++; i < sz(bit); i += i & -i) bit[i] += v;
  }
  ll query(int i) {
    ll ret = 0;
    for (i++; i > 0; i -= i & -i) ret += bit[i];
    return ret;
  }
  int lower_bound(ll v){ // min pos st sum of [0, pos] >= sum
    int pos = 0;
    for(int j=(1 << 23); j >= 1; j/=2){
      if(pos+j < sz(bit) && bit[pos + j] < v){
        pos += j;
        v -= bit[pos];
      }
    }
    return pos;
  }
};