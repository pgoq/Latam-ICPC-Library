/**
 * Description: Computes the Minkowski sum of two convex polygons.
 * Polygons must be convex and given in CCW order.
 * Returns the vertices of the Minkowski sum polygon in CCW order.
 * Time: O(n + m)
 */

#include "Point.h"
using P = Point<ll>;

vector<P> minkowski(vector<P> p, vector<P> q) {
  auto fix = [](vector<P>& A) {
    int pos = 0;
    for (int i = 1; i < sz(A); i++) {
      if(A[i].y < A[pos].y || (A[i].y == A[pos].y && A[i].x < A[pos].x)) 
        pos = i;
    }
    rotate(A.begin(), A.begin() + pos, A.end());
    A.push_back(A[0]), A.push_back(A[1]);
  };
  fix(p), fix(q);
  vector<P> result;
  int i = 0, j = 0;
  while (i < sz(p) - 2 || j < sz(q) - 2) {
    result.push_back(p[i] + q[j]);
    auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
    if (cross >= 0 && i < sz(p) - 2) i++;
    if (cross <= 0 && j < sz(q) - 2) j++;
  }
  return result;
}