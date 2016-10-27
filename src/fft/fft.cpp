#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cassert>
#include <complex>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
typedef long long ll;
typedef long double ld;
typedef complex<ld> C;
const ld PI = 3.14159265358979323;
const ld EPS = 1e-9;

// size of input vector should be 2^n and there should be 2^(n-1) zeroes at the end
// (this is done automatically in multiplyPolynomials)
// on my machine, 3 seconds for two 10^5 polynomials

void fft(int n, vector<C>& v, bool inv) {
    if (n == 1) return;
    vector<C> even, odd;
    rep(i, 0, v.size()) ((i % 2) ? odd : even).push_back(v[i]);
    fft(n / 2, even, inv);
    fft(n / 2, odd, inv);
    C omega1 = polar((ld) 1.0, 2 * PI / n);
    if (inv) omega1 = conj(omega1);
    C omega = 1;
    rep(i, 0, n / 2) {
        v[i] = even[i] + omega * odd[i];
        v[i + n / 2] = even[i] - omega * odd[i];
        omega *= omega1;
    }
}

vector<ll> multiplyPolynomials(vector<ll> &a, vector<ll> &b) {
    int n = 1;
    while (n < a.size() || n < b.size()) n *= 2;
    n *= 2;
    
    vector<C> v[2];
    rep(j, 0, 2) {
        for (auto x : (j ? b : a)) v[j].push_back(x);
        v[j].resize(n, 0);
        fft(n, v[j], false);
    }
    
    rep(i, 0, n) v[0][i] *= v[1][i];
    fft(n, v[0], true);
    vector<ll> res(n);
    rep(i, 0, n) res[i] = llround(v[0][i].real() / n);
    return res;
}

int main() {
    // basic test
    vector<ll> p1 = {0, 1, 2, 2};
    vector<ll> p2 = { -5, 1};
    vector<ll> res = multiplyPolynomials(p1, p2);
    // expected: 0 -5 -9 -8 2 0 0 0
    for (auto x : res) cout << x << " "; cout << endl;
    
    // stress test
    vector<ll> t1, t2;
    int N = 1e5;
    rep(i, 0, N) t1.push_back(rand() - 1e9);
    rep(i, 0, N) t2.push_back(rand() - 1e9);
    multiplyPolynomials(t1, t2);
    return 0;
}