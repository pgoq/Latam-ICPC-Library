/**
 * Description: Divide and Conquer DP maintaining cost, can be used when $opt[i][j] \le opt[i][j+1]$.
 * In this code everything is 1-based. Memory can be optmized by keeping only the last row
 * Time: O(M N \log N)
 */
#pragma once

void add(int idx) {}
void rem(int idx) {}

void deC(int i, int l, int r, int optL, int optR) {
    if (l > r) return;
    int j = (l + r) / 2;
    for (int k = r; k > j; k--) rem(k);
    int opt = optL;
    for (int k = optL; k <= min(optR, j); k++) {
        // cost = cost[k, j]
        int val = dp[i - 1][k - 1] + cost;
        if (val < dp[i][j]) {
            dp[i][j] = val;
            opt = k;
        }
        rem(k);
    }
    for (int k = min(optR, j); k >= optL; k--) add(k);
    rem(j);
    deC(i, l, j - 1, optL, opt);

    for (int k = j; k <= r; k++) add(k);
    for (int k = optL; k < opt; k++) rem(k);
    deC(i, j + 1, r, opt, optR);

    for (int k = optL; k < opt; k++) add(k);
}

int solve(int N, int M) { // 1-based
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= N; j++){
            dp[i][j] = inf; // base case
        }
    }
    cost = 0; // neutral value
    for (int i = 1; i <= N; i++) add(i);
    for (int i = 1; i <= M; i++) {
        deC(i, 1, N, 1, N);
    }
    return dp[M][N];
}
