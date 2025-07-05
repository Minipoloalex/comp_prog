#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// template <typename T>
// using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

// allowing duplicates with less_equal is not a good practice, should use a pair
// can be represented as <value, index in array>
using namespace std;
using ordered_set = tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update>;

typedef int64_t ll;
typedef vector<ll> vll;
typedef pair<ll, int> lli;
typedef vector<ll> vll;
typedef vector<lli> vlli;

ll sieve_size;
bitset<1000001> bs;
vll p;

void sieve(ll upper) {
    sieve_size = upper + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i < sieve_size; i++) if (bs[i]) {
        for (ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}
vlli primeFactors(ll N) {
    vlli factors;
    for (int i = 0; i < (int) p.size() && (p[i] * p[i]) <= N; i++) {
        int _exp = 0;
        while (N % p[i] == 0) {
            N /= p[i];
            _exp++;
        }
        if (_exp != 0) {
            factors.emplace_back(p[i], _exp);
        }
    }
    if (N != 1) {
        if (factors.empty()) factors.emplace_back(N, 1);
        else {
            if (factors.back().first == N) {
                factors.back() = make_pair(factors.back().first, factors.back().second);
            }
            else {
                factors.emplace_back(N, 1);
            }
        }
    }
    return factors;
}

void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int pi;
        cin >> pi;
        pi--;
        g[pi].push_back(i);
    }
    vlli kp = primeFactors(k);
    vector<vlli> pai(n);
    for (int i = 0; i < n; i++) {
        pai[i] = primeFactors(k / gcd(k, a[i]));
    }
    vector<map<int,ordered_set>> vp(n);

    for (int t = 0; t < q; t++) {
        int u, x;
        cin >> u >> x;
        u--;
        vlli xprimes = primeFactors(x);
        for (auto &[prime, cnt]: xprimes) {
            for (int i = 0; i < cnt; i++) {
                vp[u][prime].insert({t, i});
            }
        }
    }
    // map<int,ordered_set> mp;
    vector<ordered_set> mp(int(5e4));
    vector<int> ans(n, -1);
    function<void(int)> dfs = [&](int u) {
        for (auto &[prime, os]: vp[u]) {
            for (auto &_p: os) {
                mp[prime].insert(_p);
            }
        }
        bool possible = true;
        int mx = 0;
        for (auto &[prime, cnt]: pai[u]) {
            possible &= (int(mp[prime].size()) >= cnt);
            int v = mp[prime].find_by_order(cnt - 1)->first;
            mx = max(mx, v + 1);
        }
        if (possible) {
            ans[u] = mx;
        }
        for (int v: g[u]) {
            dfs(v);
        }
        for (auto &[prime, os]: vp[u]) {
            for (auto &_p: os) {
                mp[prime].erase(_p);
            }
        }
    };
    dfs(0);
    for (int an: ans) cout << an << " ";
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    sieve(int(5e4));
    while (t--) {
        solve();
    }
    return 0;
}
