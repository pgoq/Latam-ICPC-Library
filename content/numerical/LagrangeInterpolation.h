/**
 * Description: Returns $P(x)$, where $P$ is the unique polynomial of degree
 * $\leq |pts| - 1$ such that $\forall i,\; P(i) = pts[i]$.
*/
ll lagrangeiro(const vector<ll> &pts, ll x)
{
	int n = sz(pts);
	vector<ll> pref(n, 1), suf(n, 1);
	for (int i=1; i<n; i++) pref[i] = mul(pref[i-1], x-(i-1));
	for (int i=n-2; i>=0; i--) suf[i] = mul(suf[i+1], x-(i+1));
	ll y = 0;
	for (int i=0; i<n; i++) {
		ll oi = pts[i];
		oi = mul(oi, mul(pref[i], mul(suf[i], mul(ifat[i], ifat[n-i-1]))));
		if ((n-i-1) % 2 == 1) oi *= -1;
		y = (y + oi) % mod;
	}
	return (y + mod) % mod;
}
