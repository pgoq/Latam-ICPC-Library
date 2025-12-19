#pragma once
//is n primitive root of p ?
bool test(ll x, ll p) {
    ll m = p - 1;
    for (ll i = 2; i * i <= m; ++i) if (!(m % i)) {
        if (modpow(x, i, p) == 1) return false;
        if (modpow(x, m / i, p) == 1) return false;
    }
    return true;
}
//find the smallest primitive root for p
ll search(ll p) {
    for (ll i = 2; i < p; i++) if (test(i, p)) return i;
    return -1;
}