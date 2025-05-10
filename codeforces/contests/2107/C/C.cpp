#include <bits/stdc++.h>
using namespace std;

const int64_t inf = int64_t(1e12);

void solve() {
    int64_t n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;

    auto mx_subarray_sm = [&]() {
        vector<int64_t> ans(n, 0);
        int64_t sm = 0;
        for (int i = 0; i < n; i++) {
            if (sm < 0) sm = 0;
            sm += a[i];
            ans[i] = sm;
        }
        return ans;
    };
    auto get_mx = [&]() {
        vector<int64_t> aux = mx_subarray_sm();
        return *max_element(aux.begin(), aux.end());
    };
    int64_t mx = get_mx();

    bool ans;
    if (mx == k) {
        ans = true;
    }
    else {
        if (mx > k) {
            // handle decreasing
            int64_t v = 0, mx2 = 0;
            for (int i = 0; i < n; i++) {
                if (v < 0) {
                    v = 0;
                }
                if (s[i] == '0') {
                    a[i] = -inf;
                }
                v += a[i];
                mx2 = max(mx2, v);    // k >= 1 so no problem here
            }
            mx = mx2;
        }
        if (mx <= k) {
            vector<int64_t> s1 = mx_subarray_sm();
            reverse(a.begin(), a.end());
            vector<int64_t> s2 = mx_subarray_sm();
            reverse(s2.begin(), s2.end());
            reverse(a.begin(), a.end());

            vector<int64_t> sm = s1;
            for (int i = 0; i < n; i++) {
                sm[i] += s2[i] - a[i];
            }
            if (mx < k) {
                // handle increasing
                int64_t mx_along_0s = INT64_MIN;
                int idx0 = -1;
                for (int i = 0; i < n; i++) {
                    if (s[i] == '0' && sm[i] > mx_along_0s) {
                        mx_along_0s = sm[i];
                        idx0 = i;
                    }
                }
                if (idx0 == -1) {
                    ans = false;
                }
                else {
                    ans = true;
                    a[idx0] += k - mx_along_0s;
                }
            }
            else ans = true;
        }
        else ans = false;
    }

    if (!ans) {
        cout << "NO\n";
    }
    else {
        cout << "YES\n";
        for (auto &ai: a) cout << ai << " ";
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
