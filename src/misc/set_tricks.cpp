/**
 * Author: Václav Volhejn
 * Description: Functions to get the closest lower element in a set.
 *  Given $S$, $k$, returns $\max \{x \in S; x \leq k\}$, or $-\infty$
 *  if there is no suitable element. Strict version replaces $\leq$ with $<$.
 * Status: tested
 */
#include "../base.hpp"
typedef long long t;
const t INF = 1e18;

t closestLower(set<t>& s, t k) {
    auto it = s.upper_bound(k);
    return (it == s.begin()) ? -INF : *(--it);
}

t closestLowerStrict(set<t>& s, t k) {
    auto it = s.lower_bound(k);
    return (it == s.begin()) ? -INF : *(--it);
}
