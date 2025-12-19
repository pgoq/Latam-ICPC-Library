/**
 * Description:Finds an extreme vertex of a convex polygon according to a unimodal comparator.
 * The comparator defines a total order along the polygon (given in CCW order).
 * Time: O(\log n)
 */
#include "Point.h"
using P = Point<ll>;
int extreme(vector<P> &pol, const function<bool(P, P)>& cmp) {
  int n = pol.size();
  auto extr = [&](int i, bool& cur_dir) {
    cur_dir = cmp(pol[(i+1)%n], pol[i]);
    return !cur_dir and !cmp(pol[(i+n-1)%n], pol[i]);
  };
  bool last_dir, cur_dir;
  if (extr(0, last_dir)) return 0;
  int l = 0, r = n;
  while (l+1 < r) {
    int m = (l+r)/2;
    if (extr(m, cur_dir)) return m;
    bool rel_dir = cmp(pol[m], pol[l]);
    if ((!last_dir and cur_dir) or
          (last_dir == cur_dir and rel_dir == cur_dir)) {
      l = m;
      last_dir = cur_dir;
    } else r = m;
  }
  return l;
}
int max_dot(vector<P> &pol, P v) {
  return extreme([&](P p, P q) { return p.dot(v) > q.dot(v); });
}
