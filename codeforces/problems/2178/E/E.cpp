#include <bits/stdc++.h>
using namespace std;


int64_t ask(int l, int r) {
    cout << "? " << l+1 << " " << r+1 << endl;
    int64_t sum;
    cin >> sum;
    return sum;
}
void finish(int64_t m) {
    cout << "! " << m << endl;
}

void go(int l, int r) {
    int64_t cursum = ask(l, r);
    if (l == r) {
        finish(cursum);
        return;
    }
    int lo = l, hi = r;
    while (lo < hi) {
        int m = lo + (hi - lo + 1) / 2;
        int64_t sml = ask(l, m);
        int64_t smr = cursum - sml;
        if (sml <= smr) {
            lo = m;
        }
        else {
            hi = m - 1;
        }
    }
    int m = lo;
    int szl = m - l + 1;
    int szr = r - m;
    if (szl < szr) {
        go(l, m);
    }
    else {
        go(m + 1, r);
    }
}

void solve() {
    int n;
    cin >> n;
    go(0, n-1);
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
