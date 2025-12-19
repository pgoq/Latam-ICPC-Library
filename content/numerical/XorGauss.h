#pragma once
struct XorGauss {
    int N;
    vector<ll> basis, who, mask;
    XorGauss(int N) : N(N), basis(N), who(N), mask(N) {}
    // if(ans & (1ll << j)) who[j] was used to form x
    bool belong(ll x){
        ll ans = 0;
        for(int i=N-1; i>=0; i--){
            if((x ^ basis[i]) < x){
                ans ^= mask[i];
                x ^= basis[i];
            }
        }
        return (x == 0);
    }
    void add(ll v, int idx) {
        ll msk = 0;
        for (int i = N - 1; i >= 0; i--) {
            if (!(v & (1ll << i))) continue;
            if (basis[i] == 0) {
                basis[i] = v, who[i] = idx;
                mask[i] = (msk | (1ll << i));
                return;
            }
            msk ^= mask[i];
            v ^= basis[i];
        }
    }
};