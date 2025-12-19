// Discrete Root
/**
 * Description: Returns $x$ such that $x^k \bmod m = a \bmod m$. 
 * If no such $x$ exists, returns $-1$.
 * Time: O(sqrt(m) * log(sqrt(m))
 */


#include "PrimitiveRoot.h"
#include "DiscreteLog.h"

ll discreteRoot(ll k, ll a, ll m) {
    ll g = primitiveRoot(m);
    ll y = discreteLog(fexp(g, k, m), a, m);
    if (y == -1) return y;
    return fexp(g, y, m);
}