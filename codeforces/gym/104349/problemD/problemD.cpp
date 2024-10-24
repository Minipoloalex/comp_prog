#include <bits/stdc++.h>
using namespace std;

int solve_lis(vector<int> &r) {
    int n = (int) r.size();
    vector<int> ans(1, r[0]);
    for (int i = 1; i < n; i++) {
        auto it = lower_bound(ans.begin(), ans.end(), r[i]);    // smallest element x >= r[i]
        if (it == ans.end()) {    // no element (i.e. r[i] > ans.back())
            ans.push_back(r[i]);
        }
        else {
            *it = r[i];
        }
    }
    return (int) ans.size();
}

int solve_lcs(vector<int> &a, vector<int> &b) {
    // Reducing LCS problem with permutations to LIS
    int n = int(a.size());  // n = a.sz = b.sz
    vector<int> b_positions(n);
    for (int i = 0; i < n; i++) {
        b_positions[b[i] - 1] = i;
    }

    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        r[i] = b_positions[a[i] - 1];
    }
    return solve_lis(r);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        int lcs_ans = solve_lcs(a, b);
        // cout << lcs_ans << " ";
        cout << (n - lcs_ans) * 2 << '\n';
    }
    return 0;
}
