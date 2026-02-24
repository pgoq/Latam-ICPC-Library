void precalc(){
	expb[0] = 1;
	rep(i,1,MAXN)
		expb[i] = (expb[i-1]*base)%MOD;
}
struct StringHash{
	vector<ll> hsh;
	StringHash(string &s) : hsh(sz(s) + 1){
		rep(i,0,sz(s))
			hsh[i+1] = (hsh[i] * base % MOD + s[i]) % MOD;
	}
	ll gethash(int l, int r){
		return (MOD + hsh[r+1] - hsh[l]*expb[r-l+1] % MOD ) % MOD;
	}
};