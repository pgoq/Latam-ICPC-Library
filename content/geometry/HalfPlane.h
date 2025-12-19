/**
 * Description: Computes the intersection of a set of half-planes.
 * Half-planes are sorted by angle and processed with a deque,
 * removing redundant or conflicting constraints.
 * Parallel half-planes are handled explicitly.
 * Returns the convex polygon of the intersection, or empty if infeasible.
 * Time: O(n \log n)
 */

#include "Point.h"
using ld = long double;
using P = Point<ld>;

struct Hp { // Half plane struct
  // 'p' is a passing point of the line and 'pq' is the direction vector of the line.
  P p, pq; 
  ld angle;

  Hp() {}
  Hp(const P& a, const P& b) : p(a), pq(b - a) {
    angle = atan2l(pq.y, pq.x);    
  }
  bool out(const P& r) { return pq.cross(r - p) < -eps; }
  bool operator < (const Hp& e) const { 
    return angle < e.angle;
  } 
  friend P inter(const Hp& s, const Hp& t) {
    ld alpha = (t.p - s.p).cross(t.pq) / s.pq.cross(t.pq);
    return s.p + (s.pq * alpha);
  }
};

vector<P> hp_intersect(vector<Hp>& H) { 
  P box[4] = { P(inf, inf), P(-inf, inf), 
               P(-inf, -inf), P(inf, -inf) };

  for(int i = 0; i<4; i++) {
    Hp aux(box[i], box[(i+1) % 4]);
    H.push_back(aux);
  }
  sort(all(H));
  deque<Hp> dq;
  int len = 0;
  for(int i = 0; i < sz(H); i++) {
    while(len>1 && H[i].out(inter(dq[len-1], dq[len-2]))){
      dq.pop_back();
      --len;
    }
    while (len > 1 && H[i].out(inter(dq[0], dq[1]))){
      dq.pop_front();
      --len;
    }
    if(len && fabsl(H[i].pq.cross(dq[len-1].pq)) < eps){
      if (H[i].pq.dot(dq[len-1].pq) < 0.0)
        return vector<P>();
      if (H[i].out(dq[len-1].p)) {
        dq.pop_back();
        --len;
      }
      else continue;
    }
    dq.push_back(H[i]);
    ++len;
  }

  while(len> 2 && dq[0].out(inter(dq[len-1], dq[len-2]))){
    dq.pop_back();
    --len;
  }
  while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))){
    dq.pop_front();
    --len;
  }
  if (len < 3) return vector<P>();
  vector<P> ret(len);
  for(int i = 0; i+1 < len; i++) {
    ret[i] = inter(dq[i], dq[i+1]);
  }
  ret.back() = inter(dq[len-1], dq[0]);
  return ret;
}