/**
 * Description: When doing DP on intervals: $dp[i][j] = \min_{i < k < j}(dp[i][k] + dp[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Another sufficient criteria is: $opt[i][j-1] \le opt[i][j] \le opt[i+1][j]$
 * Time: O(N^2)
 */
#pragma once

ll knuth(){
    memset(opt, -1, sizeof opt);
    for(int i=n-1; i>=0; i--){
        dp[i][i] = 0; // base case
        opt[i][i] = i;
        for(int j=i+1; j<n; j++){
            int optL = (!j ? 0 : opt[i][j-1]);
            int optR = (~opt[i+1][j] ? opt[i+1][j] : n-1);
            ll cst = cost(i, j);
            dp[i][j] = INF;
            optL = max(i, optL), optR = min(j-1, optR);
            for(int k=optL; k<=optR; k++){
                ll now = dp[i][k] + dp[k+1][j] + cst;
                if(now <= dp[i][j]){
                    dp[i][j] = now;
                    opt[i][j] = k;
                }
            }
        }
    }
}