#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n);
    vector<int> l(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
        a[i].resize(l[i]);
        for (int j = 0; j < l[i]; j++) {
            cin >> a[i][j];
        }
    }
    int T = accumulate(l.begin(), l.end(), 0);
    vector<int> freq(T);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l[i]; j++) {
            int v = a[i][j];
            if (v < T) freq[v]++;
        }
    }

    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int sz = l[i]+1;
        vector<int> arr_freq(sz);
        for (int j = 0; j < l[i]; j++) {
            int v = a[i][j];
            if (v < sz) arr_freq[v]++;
        }
        int cur_score = 0;
        for (int v = 0; v < sz; v++) {
            if (arr_freq[v] > 0) cur_score++;
            else break;
        }
        int imp_val = cur_score;
        int imp_score = cur_score + 1;
        for (int v = imp_score; v < sz; v++) {
            if (arr_freq[v] > 0) imp_score++;
            else break;
        }

        for (int j = 0; j < l[i]; j++) { // a[i,j] from this array to any other (any k)
            int v = a[i][j];
            int score = cur_score;
            if (v < sz) {
                if (arr_freq[v] == 1) {
                    score = min(score, v);
                }
            }
            ans += int64_t(score) * (n - 1); // (i, j) from this, k any other
        }

        // (i, j) any other, k here
        // receive the specific value that improves this array's score
        ans += int64_t(freq[imp_val]) * imp_score;

        // receive other values that we do not care but keep our score
        ans += int64_t(T - l[i] - freq[imp_val]) * cur_score;

        // (i, j) any other, k any other as well
        ans += int64_t(cur_score) * (T - l[i]) * (n - 2);
    }
    cout << ans << '\n';
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
