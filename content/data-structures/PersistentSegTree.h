/**
 * 
 * Usage: SegP(size of the segtree, number of updates)
 * 
 * roots = {0}, newRoot = update(roots.back(),...), roots.push(newRoot)
 */


struct SegP {
  static constexpr ll neut = 0;
  struct Node {
    ll v; // start with neutral value
    int l, r;
    Node(ll v=neut, int l=0, int r=0) : v(v), l(l), r(r){}
  };
  vector<Node> seg;
  int n, CNT;
  SegP(int _n, int upd): seg(20*(upd+_n)), n(_n), CNT(1){}
  ll merge(ll a, ll b) { return a + b; }
  int update(int root, int pos, int val, int l, int r) {
    int p = CNT++;
    seg[p] = seg[root];
    if (l == r) {
      seg[p].v += val;
      return p;
    }
    int mid = (l + r) / 2;
    if (pos <= mid){
      seg[p].l = update(seg[p].l, pos, val, l, mid);
    }else seg[p].r = update(seg[p].r,pos,val,mid+1,r);

    seg[p].v=merge(seg[seg[p].l].v, seg[seg[p].r].v);
    return p;
  }
  int query(int p, int L, int R, int l, int r) {
    if (l > R || r < L) return neut;
    if (L <= l && r <= R) return seg[p].v;
    int mid = (l + r) / 2;
    int left = query(seg[p].l, L, R, l, mid);
    int right = query(seg[p].r, L, R, mid + 1, r);
    return merge(left, right);
  }
  int update(int root, int pos, int val) {
    return update(root, pos, val, 0, n - 1);
  }
  int query(int root, int L, int R) {
    return query(root, L, R, 0, n - 1);
  }
};