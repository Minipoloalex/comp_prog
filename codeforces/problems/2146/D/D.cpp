#include <bits/stdc++.h>
using namespace std;

int sz(int n) {
    for (int i = 0; ; i++) {
        if ((n >> i) == 0) {
            return i;
        }
    }
}

vector<int> solve1(int r) {
    vector<int> ans(r+1,-1);
    for (int i = r; i >= 0; i--) if (ans[i] == -1) {
        int msk_sz = sz(i);
        int mask = (1 << msk_sz) - 1;
        int other = (~i) & mask;    // easy to see that other < i
        assert(ans[other] == -1);
        ans[other] = i;
        ans[i] = other;
    }
    return ans;
}

void solve(int l, int add, int x, int y, vector<int> &ans) {
    if (x > y) return;

    if (x == y) {
        ans[(x | add) - l] = x | add;
        return;
    }
    int xsz = sz(x);
    int ysz = sz(y);
    if (xsz == ysz) {
        // this effectively uses the bit (if equal, we need to recurse to next lower bit)
        int nbit = 1 << (xsz-1);
        solve(l, add | nbit, x ^ nbit, y ^ nbit, ans);
        return;
    }
    int gor = 1 << (ysz-1);
    int gol = gor - 1;
    while (true) {
        if (gor > y) {
            solve(l, add, x, gol, ans);
            return;
        }
        if (gol < x) {
            solve(l, add, gor, y, ans);
            return;
        }
        ans[(gor | add) - l] = (gol | add);
        ans[(gol | add) - l] = (gor | add);
        gor++;
        gol--;
    }
}

vector<int> solve2(int l, int r) {
    vector<int> ans(r-l+1,-1);
    solve(l, 0, l, r, ans);
    return ans;
}

void solve() {
    int l, r;
    cin >> l >> r;
    auto v = solve2(l, r);
    int64_t ans = 0;
    for (int i = 0; i < r-l+1; i++) {
        ans += (l+i) | v[i];
    }
    cout << ans << '\n';
    for (int i = 0; i < r-l+1; i++) {
        cout << v[i] << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
