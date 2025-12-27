/**
 * Description: In Segment Tree Beats, `lazy` does NOT mean "updates still missing here".
 * The node already reflects all previous updates. Instead, `lazy` stores what
 * must be propagated to the children before recursing. Always call `apply(l,r,p)`
 * before descending. This node layout supports range add, range chmin and range
 * chmax operations.
 * Beats conditions:
 * 
 * break:  MIN x: mx1 <= x  ;  MAX x: mi1 >= x
 * 
 * tag:    MIN x: x > mx2  ;   MAX x:  x < mi2 
 *  
 * Time: amortized O(\log^2 N), without range add O(\log N)
 * 
 */

struct node{
  ll mx1, mx2, sum, lazy;
  ll mi1, mi2;
  int cMax, cMin, tam;
  node(int x=0) : mx1(x),mx2(-inf),mi1(x),mi2(inf),
              cMax(1),cMin(1),tam(1),sum(x),lazy(0){}
  node(node a, node b){
    sum = a.sum+b.sum, tam = a.tam+b.tam;
    lazy = 0;
    mx1 = max(a.mx1, b.mx1);
    mx2 = max(a.mx2, b.mx2);
    if(a.mx1 != b.mx1) mx2 = max(mx2, min(a.mx1, b.mx1));
    cMax=(a.mx1==mx1 ? a.cMax:0)+(b.mx1==mx1 ? b.cMax:0);

    mi1 = min(a.mi1, b.mi1);
    mi2 = min(a.mi2, b.mi2);
    if(a.mi1 != b.mi1) mi2=min(mi2, max(a.mi1, b.mi1));
    cMin=(a.mi1==mi1 ? a.cMin:0)+(b.mi1==mi1 ? b.cMin:0);
  }
  void apply_sum(ll x){
    mx1 += x, mx2 += x,mi1 += x, mi2 += x;
    sum += tam*x, lazy += x;
  }
  void apply_min(ll x){
    if(x >= mx1) return;
    sum -= (mx1 - x)*cMax;
    if(mi1 == mx1) mi1 = x;
    if(mi2 == mx1) mi2 = x; 
    mx1 = x;
  }
  void apply_max(ll x){
    if(x <= mi1) return;
    sum -= (mi1 - x)*cMin;
    if(mx1 == mi1) mx1 = x;
    if(mx2 == mi1) mx2 = x;
    mi1 = x;
  }
};
void apply(int l, int r, int p){
  for(int i=2*p+1; i<=2*p+2; i++){
    seg[i].apply_sum(st[p].lazy);
    seg[i].apply_min(st[p].mx1);
    seg[i].apply_max(st[p].mi1);
  }   
  seg[p].lazy = 0;
}