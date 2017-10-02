#include "../base.hpp"

// Higher weights are higher.
// Primarily used as a set able to get the k-th element

#define SIZE(t) ((t) ? (t)->size : 0)

struct Treap {
    Treap *lson = NULL, *rson = NULL;
    ll val;
    int weight;
    int size = 0;
    
    Treap(ll _val) : val(_val), weight(rand()), size(1) {}
    
    ~Treap() {
        delete lson;
        delete rson;
    }
    
    void setSon(bool right, Treap *newSon) {
        Treap *&upd = right ? (rson) : (lson);
        upd = newSon;
        size = 1 + SIZE(lson) + SIZE(rson);
    }
};

Treap* merge(Treap *l, Treap *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->weight > r->weight) {
        l->setSon(true, merge(l->rson, r));
        return l;
    } else {
        r->setSon(false, merge(l, r->lson));
        return r;
    }
}

pair<Treap*, Treap*> split(Treap *a, ll val) {
    if (!a) return {NULL, NULL};
    if (a->val <= val) {
        pair<Treap*, Treap*> res = split(a->rson, val);
        a->setSon(true, res.first);
        return {a, res.second};
    } else {
        pair<Treap*, Treap*> res = split(a->lson, val);
        a->setSon(false, res.second);
        return {res.first, a};
    }
}

void insert(Treap *&a, ll val) {
    if (!a) {
        a = new Treap(val);
    } else {
        pair<Treap*, Treap*> spl = split(a, val);
        a = merge(spl.first, new Treap(val));
        a = merge(a, spl.second);
    }
}

// TODO: works only for integers; all elements in the treap must be unique
void erase(Treap *&a, ll val) {
	pair <Treap *, Treap *> spl = split(a, val);
	pair <Treap *, Treap *> spl2 = split(spl.first, --val);
	assert(spl2.second->size == 1);
	delete spl2.second;
	a = merge(spl2.first, spl.second);
}

ll getKth(Treap *a, int k) { //zero-indexed
    assert(k < a->size);
    while (true) {
        int lsize = SIZE(a->lson);
        if (lsize == k)
            return a->val;
        else if (lsize > k)
            a = a->lson;
        else
            a = a->rson, k -= lsize + 1;
    }
}

int indexOf(Treap *a, ll val) {
    int res = 0;
    while (true) {
        if (!a) return -1;
        int lsize = SIZE(a->lson);
        if (a->val == val)
            return res + lsize;
        else if (val < a->val)
            a = a->lson;
        else
            res += lsize + 1, a = a->rson;
    }
}
