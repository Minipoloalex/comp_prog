#include <bits/stdc++.h>
using namespace std;

// meet in the middle

const int MAX_N = 40;
int n, x;
int half;
int a[MAX_N];

vector<int> occl, occr;

void get_subset_sums(int l, int r, int curr, vector<int> &occ) {
    // [l, r)
    if (curr > x) return;
    if (l == r) {
        occ.push_back(curr);
        return;
    }

    get_subset_sums(l + 1, r, curr + a[l], occ);
    get_subset_sums(l + 1, r, curr, occ);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin >> n >> x;
    for (int i = 0; i < n; i++) cin >> a[i];

    half = n / 2;

    get_subset_sums(0, half, 0, occl);
    get_subset_sums(half, n, 0, occr);
    sort(occr.begin(), occr.end());
    int64_t ans = 0;
    for (int v: occl) {
        int val = x - v;
        int cnt = int(upper_bound(occr.begin(), occr.end(), val) - lower_bound(occr.begin(), occr.end(), val));
        ans += cnt;
    }
    cout << ans << '\n';
    return 0;
}
