#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    // better solution with prefix sums and suffix max of prefix sums
    auto get_ans = [&](int &smallest) {
        bool ans = false;
        bool optimal_first_found = false;
        int cnt = 0;
        for (int i = 0; i < n && !ans; i++) {
            int sz = i + 1;
            cnt += a[i] <= k;
            int cntbad = sz - cnt;
            if (cnt >= 2 && cnt > cntbad && i < n - 1) {
                ans = true;
            }
            if (cnt == cntbad && optimal_first_found && i < n - 1) {
                ans = true;
            }
            if (cnt == cntbad) {
                optimal_first_found = true;
            }

            if (cnt >= cntbad && smallest == INT_MAX) {
                smallest = i;
            }
        }
        return ans;
    };
    int smallest_left = INT_MAX, smallest_right = INT_MAX;
    bool ans = get_ans(smallest_left);
    if (!ans) {
        reverse(a.begin(), a.end());
        ans |= get_ans(smallest_right);
    }
    if (!ans && smallest_left != INT_MAX && smallest_right != INT_MAX) {
        int total_elems = smallest_left + 1 + smallest_right + 1;
        if (total_elems < n) {
            ans = true;
        }
    }
    cout << (ans ? "YES" : "NO") << '\n';
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
