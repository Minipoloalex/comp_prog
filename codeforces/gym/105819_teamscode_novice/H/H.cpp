#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, q; 
    cin >> n >> q;

    vector<int64_t> a(n + 1, 0), pf(n + 1, 0);

    a[1] = a[2] = 1;
    for (int i = 3; i <= n; i++) {
        a[i] = a[i-1] + a[i-2];
    }
    
    pf[1] = 1;
    for (int i = 2; i <= n; i++) {
        pf[i] = pf[i-1] + a[i];
    }

    pf[n] = pf[n-2] + 1;

    const int lim = int(5e6 + 10);
    const int inf = int(1e9);
    vector<int64_t> x(lim, inf);
    x[0] = 0;

    for (int i = 0; i < lim; i++) {
        for (int j = 1; j < 31; j++) {
            int64_t idx = i + pf[j]; 
            if (idx >= lim) continue;
            x[idx] = min(x[idx], x[i] + 1);
        }
    }

    for (int i = 0; i < q; i++) {
        int64_t qa, qb, tg;
        cin >> qa >> qb >> tg;

        int64_t sum = qa + qb;
        for (int k = 3; k <= n; k++) {
            int64_t tmp = qb;
            qb = qa + qb;
            qa = tmp;

            sum += qb;
        }

        tg -= sum;

        if (tg < 0) cout << -1 << '\n';
        else {
            assert(tg <= lim);
            cout << x[tg] << '\n';
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
