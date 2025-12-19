/**
 * Description: Block size should be around $(2 * N * N)^{\frac{1}{3}}$
 * Usage: intervals are [l, r], addQuery(l, r, number of updates happened before this query, index of query),
 * addUpdate(index of updated position, value before update, value after update)
 * Time: O(Q * (2 * N * N)^{\frac{1}{3}} * F)
 */

const int B = 2700;
struct MoUpdate {
  struct Query {
    int l, r, t, idx;
    Query(int l, int r, int t, int idx) 
      : l(l), r(r), t(t), idx(idx) {}
    bool operator < (const Query& p) const {
      if (l / B != p.l / B) return l < p.l;
      if (r / B != p.r / B) return r < p.r;
      return t < p.t;
    }
  };
  struct Upd {
    int i, old, now;
    Upd(int i, int old, int now): i(i),old(old),now(now){}
  };

  vector<Query> queries;
  vector<Upd> updates;

  void addQuery(int l, int r, int t, int idx) { 
    queries.push_back(Query(l, r, t, idx)); }
  void addUpdate(int i, int old, int now) { 
    updates.push_back(Upd(i, old, now)); }

  void add(int x) {} // F
  void rem(int x) {} // F
  int getAns() {}
  void update(int novo, int idx, int l, int r) {
    if (l <= idx && idx <= r) rem(idx);
    arr[idx] = novo;
    if (l <= idx && idx <= r) add(idx);
  }

  void solve() {
    int l = 0, r = -1, t = 0;
    sort(queries.begin(), queries.end());
    for (Query q : queries) {
      while (l > q.l) add(--l);
      while (r < q.r) add(++r);
      while (l < q.l) rem(l++);
      while (r > q.r) rem(r--);
      while (t < q.t) {
        auto u = updates[t++];
        update(u.now, u.i, l, r);
      }
      while (t > q.t) {
        auto u = updates[--t];
        update(u.old, u.i, l, r);
      }
      ans[q.idx] = getAns();
    }
  }
};