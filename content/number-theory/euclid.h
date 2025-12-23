/**
 * Description: Find $x,y$ such that $Ax+By=\gcd(A,B)$.
 * If $\gcd(A,B)=1$, then $x=A^{-1}\!\!\pmod B$ and $y=B^{-1}\!\!\pmod A$.
 * Time: O(\log)
 */
#pragma once

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}