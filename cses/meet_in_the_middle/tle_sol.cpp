#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 40;
int n, x;
int half;
int a[MAX_N];
map<int, int64_t> cnt;

void second(int idx, int curr) {
    if (curr > x) return;
    if (idx == n) {
        cnt[curr]++;
        return;
    }

    second(idx + 1, curr + a[idx]);
    second(idx + 1, curr);
}

int64_t first(int idx, int curr) {
    if (curr > x) return 0;
    if (idx == half) {
        return cnt[x - curr];
    }
    return first(idx + 1, curr + a[idx]) + first(idx + 1, curr);
}

// TLE because too many combinations and size of map is too big

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin >> n >> x;
    for (auto &ai: a) cin >> ai;

    half = n / 2;
    second(half, 0);

    int64_t ans = first(0, 0);
    cout << ans << '\n';

    return 0;
}
