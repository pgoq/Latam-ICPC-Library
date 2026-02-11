/**
 * Description: Disjoint-set data structure with bipartite check
 */
#pragma once
struct Uf{
    vector<int> tam, ds, bi, c;
    Uf(int n) : tam(n, 1), ds(n), bi(n, 1), c(n){
        iota(all(ds), 0);
    }
    int find(int i){ return (i==ds[i] ? i : find(ds[i]));}
    int color(int i){ 
        return (i==ds[i] ? 0 : (c[i]^color(ds[i])));}
    void merge(int a, int b){
        int ca = color(a), cb = color(b);
        a = find(a), b = find(b);
        if(a == b){
            if(ca == cb) bi[a] = false;
            return;
        }
        if(tam[a] < tam[b]) swap(a, b);
        ds[b] = a, tam[a] += tam[b];
        bi[a] = (bi[a] && bi[b]);
        c[b] = (ca ^ cb ^ 1);
    }
};