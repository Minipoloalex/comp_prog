#include <bits/stdc++.h>
using namespace std;

const int64_t MAX = int64_t(1e18);

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    sort(a.begin(), a.begin() + l - 1);
    // for (int x: a) cout << x << " ";
    // cout << endl;

    sort(a.begin() + l - 1, a.begin() + r);
    reverse(a.begin() + l - 1, a.begin() + r);
    // for (int x: a) cout << x << " ";
    // cout << endl;
    
    sort(a.begin() + r, a.end());
    // for (int x: a) cout << x << " ";
    // cout << endl;

    vector<int64_t> middle(r - l + 1, 0), left(l - 1, 0), right(n - r, 0);
    int64_t sum = 0;
    for (int i = l - 1; i < r; i++) {
        int middle_idx = i - (l - 1);
        if (middle_idx > 0) {
            middle[middle_idx] += middle[middle_idx - 1];
        }
        middle[middle_idx] += a[i];
        sum += a[i];
    }
    for (int i = 0; i < l - 1; i++) {
        left[i] += a[i];
        if (i > 0) {
            left[i] += left[i - 1];
        }
    }
    for (int i = r; i < n; i++) {
        int ridx = i - r;
        right[ridx] += a[i];
        if (ridx > 0) {
            right[ridx] += right[ridx - 1];
        }
    }
    
    int64_t ans = sum;
    auto get_biggest = [&](int sz) -> int64_t {
        return middle[sz - 1];
    };
    auto get_smallest_first = [&](int sz) -> int64_t {
        if (sz - 1 >= l - 1) return MAX;
        return left[sz - 1];
    };
    auto get_smallest_second = [&](int sz) -> int64_t {
        if (sz - 1 >= n - r) return MAX;
        return right[sz - 1];
    };
    for (int sz = 1; sz <= r - l + 1; sz++) {
        int64_t biggest_sums = get_biggest(sz);
        int64_t first_smallest_sums = get_smallest_first(sz);
        int64_t second_smallest_sums = get_smallest_second(sz);
        if (first_smallest_sums != MAX) {
            ans = min(ans, sum - biggest_sums + first_smallest_sums);
        }
        if (second_smallest_sums != MAX) {
            ans = min(ans, sum - biggest_sums + second_smallest_sums);
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
