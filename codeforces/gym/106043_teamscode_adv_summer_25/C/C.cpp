#include <bits/stdc++.h>
using namespace std;

vector<int> prv_greater(int n, vector<int> const&a) {
    stack<int> s;
    vector<int> prv(n);
    for (int i = 0; i < n; i++) {
        while (!s.empty() && a[s.top()] <= a[i]) {
            s.pop();
        }
        if (!s.empty()) {
            prv[i] = s.top();
        }
        else {
            prv[i] = -1;
        }
        s.push(i);
    }
    return prv;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    vector<int> prv = prv_greater(n, a);

    reverse(a.begin(), a.end());
    vector<int> nxt = prv_greater(n, a);
    reverse(a.begin(), a.end());

    reverse(nxt.begin(), nxt.end());
    for (int i = 0; i < n; i++) {
        nxt[i] = n - 1 - nxt[i];
    }

    vector<int> has(n + 1);
    for (int i = 0; i < n; i++) {
        if (a[i] <= n) {
            has[a[i]] = true;
        }
    }
    int mex = 0;
    while (has[mex]) mex++;
    vector<int> mx_size(mex, INT_MIN);
    for (int i = 0; i < n; i++) {
        if (a[i] < mex) {
            int r = nxt[i];
            int l = prv[i];
            int mx_array_sz = r - l - 1;
            mx_size[a[i]] = max(mx_size[a[i]], mx_array_sz);
        }
    }
    vector<vector<int>> subarray_values(n + 1);
    for (int i = 0; i < mex; i++) {
        subarray_values[mx_size[i]].push_back(i);
    }
    int cur = mex;
    for (int i = 1; i <= n; i++) {
        cout << cur << " ";
        for (int v: subarray_values[i]) {
            cur = min(cur, v);
        }
    }
    cout << '\n';
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
