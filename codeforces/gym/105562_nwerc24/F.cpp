#include <bits/stdc++.h>
using namespace std;

class ufds {
    int n;
    vector<int> p;
public:
    ufds(int _n): n(_n), p(_n) { iota(p.begin(), p.end(), 0); }

    int set(int x) {
        return p[x] = (x == p[x] ? x : set(p[x]));
    }

    void join(int u, int v) {
        assert(v >= u);
        int np = p[v];
        p[u] = np;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> cap(n+1, 0), cur(n+1, 0), next(n + 1, n);
    ufds ds(n + 1);
    for (int i = 0; i < n; i++) cin >> cap[i];

    stack<pair<int, int>> s;

    for (int i = n-1; i >= 0; i--) {
        while (!s.empty() && s.top().first <= cap[i]) s.pop();
        if (s.empty()) {
            next[i] = n;
        } else {
            next[i] = s.top().second;
        }
        s.emplace(cap[i], i);
    }

    function<void(int,int)> add = [&](int lvl, int quant) -> void {
        lvl = ds.set(lvl);

        if (cur[lvl] + quant <= cap[lvl]) {
            cur[lvl] += quant;
        } else {
            int df = quant - (cap[lvl] - cur[lvl]);
            cur[lvl] = cap[lvl];
            int nx = ds.set(next[lvl]);
            if (nx < n) {
                add(nx, df);
            }
        }

        if (cur[lvl] == cap[lvl]) ds.join(lvl, next[lvl]);
    };

    auto query = [&](int lvl) {
        cout << cur[lvl] << '\n';
    };

    for (; q; q--) {
        char c; cin >> c;
        if (c == '+') {
            int lvl, quant; cin >> lvl >> quant;
            add(lvl-1, quant);
        } else {
            int lvl; cin >> lvl;
            query(lvl-1);
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
