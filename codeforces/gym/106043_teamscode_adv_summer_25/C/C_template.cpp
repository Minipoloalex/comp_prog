#include <bits/stdc++.h>
using namespace std;

// These are both implicit monotonic stack-based approaches
/**
 * For each position, gives the 0-based index of the closest element on the left of it for which cmp is true
 * Gives -1 if there's none
 * Formally, for each index i, gives the first index on the left j < i, s.t. cmp(a[j], a[i]) is true
 * Usage:
 *  auto pg = closest_left(a, greater<int>());   // for previous (strictly) greater
 */
template<typename T, typename Pred>
vector<int> closest_left(const vector<T> &a, Pred cmp) {
    int n = int(a.size()); vector<int> closest(n); iota(closest.begin(), closest.end(), -1);
    for (int i = 0; i < n; i++) {
        auto &j = closest[i];
        while(j >= 0 && !cmp(a[j], a[i])) j = closest[j];
    }
    return closest;
}

/**
 * For each position, gives the 0-based index of the closest element on the right of it for which cmp is true
 * Gives a.size() if there's none
 * Formally, for each index i, gives the first index on the right j > i, s.t. cmp(a[j], a[i]) is true
 * Usage:
 *  auto ng = closest_right(a, greater<int>());   // for next (strictly) greater
 */
template<typename T, typename Pred>
vector<int> closest_right(const vector<T> &a, Pred cmp) {
    int n = int(a.size()); vector<int> closest(n); iota(closest.begin(), closest.end(), 1);
    for (int i = n - 1; i >= 0; i--) {
        auto &j = closest[i];
        while(j < n && !cmp(a[j], a[i])) j = closest[j];
    }
    return closest;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> prv = closest_left(a, greater<int>());
    vector<int> nxt = closest_right(a, greater<int>());

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
