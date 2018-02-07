/**
 * Author: Vaclav Volhejn, based on Simon Lindholm's code
 * Description: Container where you can add lines of the form $kx+m$,
 *  and query maximum values at points $x$. Assumes that the $k$s of the added
 *  are non-decreasing. Use sorted_query for cases where $x$ is non-decreasing.
 * Time: amortized $O(1)$ per add and sorted_query, $O(\log n) per query$
 */
#include "../base.hpp"

struct Line {
    mutable ll k, m, p; // p is the position from which the line is optimal
    ll val(ll x) const { return k*x + m; }
};
ll floordiv (ll a, ll b) {
    return a / b - ((a^b) < 0 && a % b);
}
// queries and line intersections should be in range (-INF, INF)
const ll INF = 1e17;

struct LineContainer : vector<Line> {
    ll isect(const Line& a, const Line& b) {
        if (a.k == b.k) return a.m > b.m ? (-INF) : INF;
        ll res = floordiv(b.m - a.m, a.k - b.k);
        if (a.val(res) < b.val(res)) res++;
        return res;
    }

    void add(ll k, ll m) {
        Line a = {k,m,INF};
        while(!empty() && isect(a, back()) <= back().p) pop_back();
        a.p = empty() ? (-INF) : isect(a, back());
        push_back(a);
    }

    ll query(ll x) {
        assert(!empty());
        int fr = 0, to = size()-1;
        ll best = -1;
        while(fr<=to) {
            int mid = (fr+to)/2;
            if ((*this)[mid].p <= x) {
                fr = mid + 1;
                best = (*this)[mid].val(x);
            } else to = mid - 1;
        }
        return best;
    }

    int qi = 0;
    ll sorted_query(ll x) {
        assert(!empty());
        qi = min(qi, (int)size() - 1);
        while(qi < size()-1 && (*this)[qi+1].p <= x) qi++;
        return (*this)[qi].val(x);
    }
};
