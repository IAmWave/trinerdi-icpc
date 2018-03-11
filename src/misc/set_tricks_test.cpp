#include "gtest/gtest.h"
#include "set_tricks.cpp"

void populateSet(set<t>& s, int n) {
    rep(i,0,n) {
        s.insert(rand());
    }
}

TEST(SET_TRICKS, WorksSame) {
    srand(123);
    set<t> s;
    populateSet(s, 100);
    for(auto &k : s) {
        EXPECT_EQ(k, closestLower(s, k));
    }
}

TEST(SET_TRICKS, WorksSameStrict) {
    srand(123);
    set<t> s;
    populateSet(s, 100);
    vector<t> v;
    for(auto k : s) v.push_back(k);
    rep(i,0,v.size()) {
        EXPECT_EQ((i==0) ? (-INF) : v[i-1], closestLowerStrict(s, v[i]));
    }
}

TEST(SET_TRICKS, Works) {
    srand(123);
    set<t> s;
    populateSet(s, 1000);
    vector<t> v;
    for(auto k : s) v.push_back(k);

    rep(i,0,1000) {
        t k = rand();
        t best = -INF;
        t bestStrict = -INF;
        rep(j,0,v.size()) {
            if(v[j] < k) {
                best = v[j];
                bestStrict = v[j];
            } else if(v[j] == k) {
                best = v[j];
            } else {
                break;
            }
        }
        EXPECT_EQ(best, closestLower(s, k));
        EXPECT_EQ(bestStrict, closestLowerStrict(s, k));
    }
    rep(i,0,v.size()) {
        EXPECT_EQ((i==0) ? (-INF) : v[i-1], closestLowerStrict(s, v[i]));
    }
}
