/**
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, inclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */

struct RMQ {
  vector<vector<int>> dp;
  RMQ(const vector<int>& a) : dp(1, a) {
    for (int i = 1, pw = 1; pw*2 <= sz(a); pw*=2, i++) {
      dp.emplace_back(sz(a) - pw*2 + 1);
      for (int j = 0; j < sz(dp[i]); j++) {
        dp[i][j] = min(dp[i-1][j], dp[i-1][j+pw]);
      }
    }
  }
  int query(int l, int r) {
    assert(l <= r);
    int k = 31 - __builtin_clz(r - l + 1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]);
  }
};
