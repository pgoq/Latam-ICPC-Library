/**
 * Description: Points called on the update function NEED to be on the $pts$ vector parameter on build.
 * Time: O((\log N)^2)
 */
#pragma once
#include "Bit.h"

struct Bit2d {
  vector<vector<int>> ys;
  vector<Bit> bit;
  vector<int> cmp_x;
  Bit2d(){}
  void put(int x, int y) {
    for (x++; x < sz(ys); x += x & -x) ys[x].push_back(y);
  }
  int id(const vector<int> &v, int y) {
    return (upper_bound(all(v), y) - v.begin()) - 1;
  }
  void build(vector<pii> pts) {
    sort(all(pts));
    for(auto p : pts) cmp_x.push_back(p.first);
    cmp_x.erase(unique(all(cmp_x)), cmp_x.end());
    ys.resize(cmp_x.size() + 1);
    for(auto p : pts) put(id(cmp_x, p.first), p.second);
    for(auto &v:ys)sort(all(v)), bit.emplace_back(sz(v));
  }
  void update(int x, int y, int val){
    x = id(cmp_x, x);
    for(x++; x < sz(ys); x+= x&-x)
      bit[x].update(id(ys[x], y), val);
  }
  int query(int x, int y){
    x = id(cmp_x, x);
    int ret = 0;
    for(x++; x > 0; x-= x&-x)
      ret += bit[x].query(id(ys[x], y));
    return ret;
  }
  int query(int x1, int y1, int x2, int y2){
    int a = query(x2, y2)-query(x2, y1-1);
    return a-query(x1-1, y2)+query(x1-1, y1-1);
  }
};