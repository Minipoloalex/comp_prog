#include <bits/stdc++.h>
using namespace std;

int solve_lis(vector<int> &r) {
    assert(!r.empty());

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

int solve_lcs_via_lis(const vector<int> &a, const vector<int> &b) {
    // Reducing LCS problem with permutations to LIS
    // assumes equal size of both sequences
    // permutations of 1-n
    assert(a.size() == b.size());

    int n = (int) b.size();
    vector<int> b_positions(n);
    for (int i = 0; i < n; i++) {
        b_positions[b[i] - 1] = i;
    }

    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        r[i] = b_positions[a[i] - 1];
    }

    int lcs_ans = solve_lis(r);
    return lcs_ans;
}

