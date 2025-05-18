#include <bits/stdc++.h>
using namespace std;

long long rng() {
	static std::mt19937 gen(
	    std::chrono::steady_clock::now().time_since_epoch().count());
	return std::uniform_int_distribution<long long>(0, INT64_MAX)(gen);
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &x: a) cin >> x;
    for (auto &x: b) cin >> x;

    vector<int64_t> pa(n + 1, 0), pb(n + 1, 0);
    map<int, int64_t> m;
    auto handle = [&](int v, set<int> &s) -> int64_t {
        if (s.find(v) != s.end()) return -1;    // already in set
        s.insert(v);

        auto it = m.find(v);
        if (it != m.end()) {
            return it->second;
        }
        return m[v] = rng();
    };
    set<int> as, bs;
    for (int i = 0; i < n; i++) {
        int64_t va = handle(a[i], as);
        pa[i + 1] = pa[i];
        if (va != -1) {
            pa[i + 1] ^= va;
        }

        pb[i + 1] = pb[i];
        int64_t vb = handle(b[i], bs);
        if (vb != -1) {
            pb[i + 1] ^= vb;
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int xi, yi;
        cin >> xi >> yi;
        int64_t va = pa[xi];
        int64_t vb = pb[yi];
        cout << (va == vb ? "Yes" : "No") << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
