#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto & x : a) cin >> x;

    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    int p1 = 0, p2 = 1;

    set<pair<int, int>> st;
    for (int i = 0; i < n; i++) st.emplace(a[i], i);

    int cnt = 0;
    while (!st.empty()) {
        if (p1 < n && p2 < n && a[p1] == a[p2]) {
            cnt++;
            st.erase(st.find({ a[p1], p1 }));
            st.erase(st.find({ a[p2], p2 }));
        } else {
            cnt++;
            st.erase(st.begin());
        }
        int i = p1;
        for (; i < n; i++) {
            if (st.find({ a[i], i }) != st.end()) break;
        }
        p1 = i;
        i = p1 + 1;
        for (; i < n; i++) {
            if (st.find({ a[i], i }) != st.end()) break;
        }
        p2 = i;
    }

    cout << cnt << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
