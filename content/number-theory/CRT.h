#pragma once

ll modinverse(ll a, ll b, ll s0 = 1, ll s1 = 0) { 
  return !b ? s0 : modinverse(b, a % b, s1, s0 - s1 * (a / b)); }

ll mul(ll a, ll b, ll m) {
  return (((__int128_t)a*b)%m + m)%m;
}

struct Equation {
  ll mod, ans;
  bool valid;
  Equation(ll a, ll m) { mod = m, ans = a, valid = true; }
  Equation() { valid = false; }
  Equation(Equation a, Equation b) {
    valid = false;
    if (!a.valid || !b.valid) return;
    ll g = gcd(a.mod, b.mod);
    if ((a.ans - b.ans) % g != 0) return;
    valid = true;
    mod = a.mod * (b.mod / g);
    ll x = mul(a.mod, modinverse(a.mod, b.mod), mod);
    ans = a.ans + mul(x, (b.ans - a.ans) / g, mod);
    ans = (ans % mod + mod) % mod;
  }
};