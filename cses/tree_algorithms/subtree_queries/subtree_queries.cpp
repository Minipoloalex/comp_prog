#include <bits/stdc++.h>
using namespace std;

#define LSB(i) ((i) & (-(i)))

class FT {
private:
    int n;
    vector<int64_t> ft;
public:
    FT(int _n) {
        n = _n + 1;
        ft.assign(n, 0);
    }
    int64_t get(int i) {
        int64_t sum = 0;
        for (; i; i -= LSB(i)) {
            sum += ft[i];
        }
        return sum;
    }
    int64_t get(int l, int r) {
        return get(r) - get(l - 1);
    }
    void update(int i, int64_t x) {
        for (int idx = i; idx < n; idx += LSB(idx)) {
            ft[idx] += x;
        }
    }
};

// euler tour technique

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (auto &vi: arr) cin >> vi;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int timer = 0;
    vector<int> st(n), end(n);
    function<void(int,int)> euler_tour = [&](int u, int p) {
        st[u] = timer++;
        for (int v: g[u]) {
            if (v != p) {
                euler_tour(v, u);
            }
        }
        end[u] = timer;
    };
    euler_tour(0, -1);
    FT ft(n);
    for (int i = 0; i < n; i++) {
        ft.update(st[i] + 1, arr[i]);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            int64_t to_add = x - arr[s];
            ft.update(st[s] + 1, to_add);
            arr[s] = x;
        }
        else {
            assert(t == 2);
            int s;
            cin >> s;
            s--;
            int64_t ans = ft.get(st[s] + 1, end[s]);
            cout << ans << '\n';
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
