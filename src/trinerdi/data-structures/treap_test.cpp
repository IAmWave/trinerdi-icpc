#include "gtest/gtest.h"
#include "treap.cpp"

void testTreapMatches(Treap* t, vector<ll>& v) {
    rep(i, 0, v.size()) {
        EXPECT_EQ(getKth(t, i), v[i]);
    }
}

vector<ll> genUnique(int n) {
    set<ll> used;
    for (int i = 0; i < n; i++) {
        ll x = rand();
        while (used.count(x)) x = rand();
        used.insert(x);
    }
    vector<ll> res;
    for (auto&x : used) {
        res.push_back(x);
    }
    return res;
}

TEST(Treap, InsertAndKth) {
    srand(123);
    rep(it, 0, 10) {
        vector<ll> v = genUnique(50);
        random_shuffle(v.begin(), v.end());
        set<ll> seen;
        Treap* t = NULL;
        for (auto &x : v) {
            insert(t, x);
            seen.insert(x);
            int i = 0;
            for (auto& y : seen) {
                EXPECT_EQ(getKth(t, i), y);
                i++;
            }
        }

    }
}

TEST(Treap, Split) {
    srand(123);
    rep(it, 0, 10) {
        vector<ll> v = genUnique(50);
        set<ll> values;
        rep(i, 0, 50) values.insert(rand());
        for (auto&x : v) values.insert(x);
        for (auto&x : v) values.insert(x);
        
        for (auto &splitval : values) {
            Treap* t = NULL;
            for (auto &x : v) insert(t, x);
            Treap *l = NULL, *r = NULL;
            tie(l, r) = split(t, splitval);
            int delta = 0;
            rep(i,0,v.size()) {
                if (v[i] <= splitval) {
                    EXPECT_NE(l, (Treap*)NULL);
                    EXPECT_EQ(getKth(l, i), v[i]);
                    delta = i+1;
                } else {
                    EXPECT_NE(r, (Treap*)NULL);
                    EXPECT_EQ(getKth(r, i-delta), v[i]);
                }
            }
        }
    }
}

TEST(Treap, Merge) {
    srand(128);
    rep(it, 0, 10) {
        vector<ll> v = genUnique(50);
        vector<ll> vl, vr;
        rep(i,0,v.size()) {
            ((i*2 < v.size())?vl:vr).push_back(v[i]);
        }
        Treap *tl = NULL, *tr = NULL;
        for(auto& x : vl) insert(tl, x);
        for(auto& x : vr) insert(tr, x);
        Treap *tm = merge(tl, tr);
        
        rep(i, 0, v.size()) {
            EXPECT_EQ(getKth(tm, i), v[i]);
        }
    }
}

TEST(Treap, BenchmarkInsertAndIndex1e5) {
    Treap* t = NULL;
    int n = 100000; // n = 10^6 takes about 5 seconds on my machine
    unordered_set<ll> used; // Elements must be different for the test to work
    for (int i = 0; i < n; i++) {
        ll x = rand();
        while (used.count(x)) x = rand();
        used.insert(x);
        insert(t, x);
    }
    for (int i = 0; i < n; i++) {
        getKth(t, i);
    }
}
