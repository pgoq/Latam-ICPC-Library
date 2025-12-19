/**
 * Description: Returns the smallest $x$ such that $a^x \bmod m = b \bmod m$. 
 * If no such $x$ exists, returns $-1$.
 * Time: O(sqrt(m) * log(sqrt(m))
 */

#pragma once
int solve(int a, int b, int m) {
    a %= m, b %= m;
    if (a == 0) return (b ? -1 : 1);
    // caso gcd(a, m) > 1
    int k = 1, add = 0, g;
    while ((g = gcd(a, m)) > 1) {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g, m /= g, ++add;
        k = (k * 1ll * a / g) % m;
    }

    int sq = sqrt(m) + 1;
    int big = 1;
    for (int i = 0; i < sq; i++) big = (1ll * big * a) % m;

    vector<pii> vals;
    for (int q = 0, cur = b; q <= sq; q++) {
        vals.push_back({ cur, q });
        cur = (1ll * cur * a) % m;
    }
    sort(all(vals));
    for (int p = 1, cur = k; p <= sq; p++) {
        cur = (1ll * cur * big) % m;
        auto it = lower_bound(all(vals), pair(cur, INF));
        if (it != vals.begin() && (--it)->first == cur) {
            return sq * p - it->second + add;
        }
    }
    return -1;
}