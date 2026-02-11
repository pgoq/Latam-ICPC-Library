/**
 * Description: If inv = 1, finds the inverse of the matrix eq and returns it as a flat vector
 * Time: O(\min(n,m)\, n m)
 */

#pragma once
struct Gauss {
  const double eps = 1e-9;
  vector<vector<double>> eq;
  void addEquation(const vector<double>& e) {
    eq.push_back(e); }
  pair<int, vector<double>> solve(int inv=0) {
    int n = sz(eq), m = sz(eq[0]) - 1 + inv;
    if(inv){
      rep(i, 0, n) eq[i].resize(2*n), eq[i][n+i] = 1;
    }
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
      int sel = row;
      rep(i, row, n) {
        if (abs(eq[i][col]) > abs(eq[sel][col])) sel = i;
      }
      if (abs(eq[sel][col]) < eps) continue;
      rep(i, col, sz(eq[0])) swap(eq[sel][i], eq[row][i]);
      where[col] = row;
      rep(i, 0, n) if (i != row) {
        double c = eq[i][col] / eq[row][col];
        rep(j, col, sz(eq[0])) eq[i][j] -= eq[row][j] * c;
      }
      ++row;
    }
    if(inv){
      vector<double> res;
      rep(i, 0, n) {
        if (where[i] == -1) return {0, {}}; // Singular
        rep(j, n, 2*n) 
          res.push_back(eq[where[i]][j] / eq[where[i]][i]);
      }
      return {1, res};
    }

    vector<double> ans(m, 0);
    rep(i, 0, m) {
      if (where[i] != -1) 
        ans[i] = eq[where[i]][m] / eq[where[i]][i];
    }
    rep(i, 0, n) {
      double sum = 0;
      rep(j, 0, m) {
        sum = sum + ans[j] * eq[i][j];
      }
      if(abs(sum - eq[i][m]) > eps)return {0, {}};
    }
    rep(i, 0, m) if (where[i] == -1) return {2, ans};
    return {1, ans};
  }
};