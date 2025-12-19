

template<const int N>
struct PartitionSolver {
  vector<vector<int>> part, to, from;
  PartitionSolver() {
    vector<int> a;
    part.push_back(a);
    gen(1, N, a);
    sort(all(part));
    to.assign(sz(part), vector<int>(N + 1, -1));
    from = to;
    for (int i = 0; i < sz(part); i++) {
      int sum = 0;
      auto arr = part[i];
      for (auto x : arr) sum += x;
      to[i][0] = i;
      from[i][0] = i;
      for (int j = 1; j + sum <= N; j++) {
        arr = part[i];
        arr.push_back(j);
        sort(all(arr));
        to[i][j] = getIndex(arr);
        from[to[i][j]][j] = i;
      }
    }
  }

  int size() const { return sz(part); }
  int getIndex(const vector<int>& arr) const { 
    return lower_bound(all(part), arr) - part.begin(); }
  int add(int id, int num) const { return to[id][num]; }
  int rem(int id, int num) const { return from[id][num]; }
  vector<int> getPartition(int id) const { 
    return part[id]; }

  void gen(int i, int sum, vector<int>& a) {
    if (i > sum) { return; }
    a.push_back(i);
    part.push_back(a);
    gen(i, sum - i, a);
    a.pop_back();
    gen(i + 1, sum, a);
  }
};

// Number of partitions for all integers <= n
vector<ll> partitionNumber(int n) {
  vector<ll> ans(n + 1, 0);
  ans[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j * (3 * j + 1) / 2 <= i; j++) {
      ll here = ans[i - j * (3 * j + 1) / 2];
      ans[i] = (ans[i] + (j & 1 ? here : -here));
    }
    for (int j = 1; j * (3 * j - 1) / 2 <= i; j++) {
      ll here = ans[i - j * (3 * j - 1) / 2];
      ans[i] = (ans[i] + (j & 1 ? here : -here));
    }
  }
  return ans;
}