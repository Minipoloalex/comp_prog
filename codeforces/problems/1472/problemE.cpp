#include <bits/stdc++.h>
using namespace std;


vector<int> solve(int n, vector<tuple<int,int,int>> &v, vector<tuple<int,int,int>> &other) {
    vector<int> mn(n);
    for (int i = n - 1; i >= 0; i--) {
        auto &[f, s, t] = other[i];

        mn[i] = s;
        if (i + 1 < n) {
            mn[i] = min(mn[i], mn[i + 1]);
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        auto &[f, s, t] = v[i];
        int lo = 0, hi = n - 1;
        int ans_idx = -1;
        while (lo <= hi && ans_idx == -1) {
            int m = (lo + hi) / 2;
            auto &[fm, sm, tm] = other[m];
            if (fm >= f) {
                lo = m + 1;
            }
            else {
                if (mn[m] >= s) {
                    hi = m - 1;
                }
                else {
                    // mn[m] < w
                    if (mn[m] == sm) {
                        ans_idx = m;
                    }
                    else {
                        lo = m + 1;
                    }
                }
            }
        }
        if (ans_idx != -1) {
            auto &[_f, _s, idx] = other[ans_idx];
            ans_idx = idx + 1;
        }
        ans[t] = ans_idx;
    }

    return ans;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<tuple<int,int, int>> v(n), rev(n);
        for (int i = 0; i < n; i++) {
            int hi, wi;
            cin >> hi >> wi;
            v[i] = make_tuple(hi, wi, i);
            rev[i] = make_tuple(wi, hi, i);
        }
        sort(v.rbegin(), v.rend());
        sort(rev.rbegin(), rev.rend());
        
        vector<int> ans1 = solve(n, v, v);
        vector<int> ans2 = solve(n, v, rev);

        for (int i = 0; i < n; i++) {
            cout << max(ans1[i], ans2[i]) << " ";
        }
        cout << '\n';
    }
    return 0;
}
