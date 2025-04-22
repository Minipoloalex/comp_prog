#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> k(n);
    for (auto &x: k) cin >> x;
    vector<int64_t> ans = k;
    stack<int> s;
    for (int i = 0; i < n; i++) {
        int width = i;
        while (!s.empty() && k[i] <= k[s.top()]) {
            s.pop();
        }
        if (!s.empty()) {
            width = max(0, i - 1 - s.top());
        }
        // cout << i << " " << width << endl;
        ans[i] += width * k[i];
        s.push(i);
    }
    s = stack<int>();
    for (int i = n - 1; i >= 0; i--) {
        int width = n - 1 - i;
        while (!s.empty() && k[i] <= k[s.top()]) {
            s.pop();
        }
        if (!s.empty()) {
            width = max(0, s.top() - (i + 1));
        }
        ans[i] += width * k[i];
        // cout << i << " " << width << endl;
        s.push(i);
    }

    int64_t mx_area = *max_element(ans.begin(), ans.end());
    cout << mx_area << '\n';
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
