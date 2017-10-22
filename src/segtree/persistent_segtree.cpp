#include "../base.hpp"

// We use exclusive right bounds everywhere; the interval is [l, r)
struct Segtree {
    int l, r;
    ll val = 0;
    Segtree *lson = NULL, *rson = NULL;
    
    Segtree(int _l, int _r, ll _val, Segtree* _lson, Segtree* _rson) :
        l(_l), r(_r), val(_val), lson(_lson), rson(_rson) {}
        
    ~Segtree() { delete lson; delete rson; }
    
    void build() {
        if (r - l > 1) {
            int mid = (l + r) / 2;
            lson = new Segtree(l, mid, 0, NULL, NULL);
            rson = new Segtree(mid, r, 0, NULL, NULL);
            lson->build(), rson->build();
        }
    }
    
    Segtree* rangeUpdate(int fr, int to, ll x) {
        if (fr >= r || l >= to) return this; // Range is not in the segment
        if (fr <= l && to >= r) { // Range is completely in the segment
            return new Segtree(l, r, val + x, lson, rson);
        }
        return new Segtree(l, r, val,
                           lson->rangeUpdate(fr, to, x),
                           rson->rangeUpdate(fr, to, x));
    }
    
    ll pointQuery(int i) const {
        if (r - l == 1) return val;
        int mid = (l + r) / 2;
        return val + ((i < mid) ? )
        if (i < mid) {
            return val + lson->pointQuery(i);
        } else {
            return val + rson->pointQuery(i);
        }
    }
};
