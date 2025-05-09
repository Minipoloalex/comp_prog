#include <bits/stdc++.h>
using namespace std;

int ask(int x) {
    cout << "? " << x + 1 << endl;
    int ans;
    cin >> ans;
    return ans;
}

void finish(int a, int b) {
    if (a == -1) {
        cout << "! -1" << endl;
    }
    else {
        cout << "! " << a << " " << b << endl;
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k), b(k);
    for (int i = 0; i < k; i++) {
        a[i] = ask(i);
    }
    for (int i = n - k; i < n; i++) {
        b[i % k] = ask(i);
    }
    bool same = true;
    int idx = INT_MAX;
    for (int i = 0; i < k; i++) {
        if (a[i] != b[i]) {
            idx = i;
            same = false;
            break;
        }
    }

    int ansa, ansb;
    if (same) {
        if (n == 2 * k) {
            ansa = k;
            ansb = k;
        }
        else {
            ansa = -1;
            ansb = -1;
        }
    }
    else {
        int rst_sz = n - 2*k;

        // binary search on size of matches for A
        int lo = 0, hi = rst_sz / k + (rst_sz % k > idx);
        while (lo < hi) {
            int m = lo + (hi - lo + 1) / 2; // m is never 0 here
            int i = k + (m - 1) * k + idx;

            int v = ask(i);
            if (a[i % k] == v) {
                lo = m;
            }
            else {
                assert(b[i % k] == v);
                hi = m - 1;
            }
        }
        // cout << "matches: " << lo << endl;
        int base = k + (lo - 1) * k + idx + 1;
        if (base < k) base = k;

        int max_sz = min(k, n - 1 - k - base + 1);  // size = r - l + 1
        vector<int> rst(max_sz);

        int mxa = 0, mxb = 0;
        for (int i = 0; i < int(rst.size()); i++) {
            int v = ask(base + i);
            int arridx = (base + i) % k;
            rst[i] = v;
            if (v == a[arridx] && i == mxa) {
                mxa++;
            }
        }
        for (int i = int(rst.size() - 1); i >= 0; i--) {
            int sz = int(rst.size() - 1) - i;
            int v = rst[i];
            int arridx = (base + i) % k;
            if (v == b[arridx] && sz == mxb) {
                mxb++;
            }
        }

        // cout << mxa << " " << mxb << endl;

        if (mxa + mxb > int(rst.size())) {
            ansa = -1;
            ansb = -1;
        }
        else {
            ansa = base + mxa;
            ansb = n - ansa;
        }
    }
    finish(ansa, ansb);
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
