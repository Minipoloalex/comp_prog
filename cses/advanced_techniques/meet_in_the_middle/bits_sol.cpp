#include <bits/stdc++.h>
using namespace std;

// meet in the middle

const int MAX_N = 40;
int n, x;
int half;
int a[MAX_N];

vector<int> occl, occr;

void get_subset_sums(int l, int r, vector<int> &occ) {
    int len = r - l;
    for (int i = 0; i < (1 << len); i++) {
        int64_t sum = 0;
        // int cpi = i;
        // while (i > 0) {
        //     // cout << i << endl;
        //     int lsb = (i) & (-i);
        //     // sum += a[l + log2(lsb)];
        //     i -= lsb;
        // }
        // i = cpi;
        for (int j = 0; j < len; j++) {
            if (i & (1 << j)) sum += a[l + j];
        }
        if (sum <= x) {
            occ.push_back(int(sum));
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin >> n >> x;
    for (auto &ai: a) cin >> ai;

    half = n / 2;

    get_subset_sums(0, half, occl);
    get_subset_sums(half, n, occr);

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
