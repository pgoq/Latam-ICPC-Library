/**
 * Description:Finds the left and right tangent points from an external point p
 * to a convex polygon given in CCW order.
 * A tangent point is a vertex where the segment p->v touches the polygon
 * without intersecting its interior, defining the limits of visibility from p.
 * Returns the indices of the left and right tangent vertices.
 * Time: O(\log n)
 */

#include "Point.h"
#include "Extreme.h"

using P = Point<ll>;

bool ccw(P p, P q, P r) {
	return (q-p).cross(r-q) > 0;
}
pair<int, int> tangents(vector<P> &pol, P p) {
    auto L = [&](P q, P r) { return ccw(p, r, q); };
    auto R = [&](P q, P r) { return ccw(p, q, r); };
    return {extreme(pol, L), extreme(pol, R)};
}