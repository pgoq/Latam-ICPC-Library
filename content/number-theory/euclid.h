/**
 * Description: Find $x,y$ such that $Ax+By=\gcd(A,B)$.
 * If $\gcd(A,B)=1$, then $x=A^{-1}\!\!\pmod B$ and $y=B^{-1}\!\!\pmod A$.
 * Time: O(\log)
 */


tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (!a) return { b, 0, 1 };
    auto [g, x, y] = ext_gcd(b % a, a);
    return { g, y - b / a * x, x };
}