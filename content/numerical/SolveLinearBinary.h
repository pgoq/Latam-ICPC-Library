/**
 * Time: O(\frac{\min(n,m)\, n m}{64})
 */

pair<int, bitset<M>> gauss(vector<bitset<M>> eq) {
    int n = eq.size(), m = M - 1;
    vector<int> where(m, -1);
    for(int col = 0, row = 0; col < m && row < n; col++){
        rep(i,row,n)
            if (eq[i][col]) {
                swap(eq[i], eq[row]);
                break;
            }
        if (!eq[row][col]) continue;
        where[col] = row;

        rep(i, 0, n) {
            if (i != row && eq[i][col]) eq[i] ^= eq[row];
        }
        ++row;
    }
    bitset<M> ans;
    rep(i,0,m) {
        if (where[i] != -1) ans[i] = eq[where[i]][m];
    }
    rep(i,0,n) {
        int sum = (ans & eq[i]).count();
        sum %= 2;
        if (sum != eq[i][m]) return pair(0, bitset<M>());
    }
    rep(i,0,m) {
        if (where[i] == -1) return pair(INF, ans);
    }
    return pair(1, ans);
}