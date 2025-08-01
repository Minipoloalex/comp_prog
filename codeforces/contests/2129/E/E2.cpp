#include <bits/stdc++.h>
using namespace std;

int ask(vector<int> ind) {
    cout << "? " << int(ind.size());
    for (int id: ind) {
        cout << " " << id;
    }
    cout << endl;
    int f;
    cin >> f;
    return f;
}

void finish(const string &ans) {
    cout << "! " << ans << endl;
}

int compute_aux(int sz) {
    int ans = 0;
    for (int i = 0; i < sz; i++) {
        for (int j = 1; j <= (1 << i); j++) {
            ans += j;
        }
    }
    return ans;
}

vector<char> handle(const vector<int> &pos, int l, int r) {
    int sz = int(pos.size());
    int simpleresult = compute_aux(sz);
    assert(sz <= 8);
    vector<int> ind;
    for (int i = sz - 1; i >= 0; i--) {
        ind.push_back(pos[i]);
        ind.push_back(r);
        for (int j = 0; j < (1 << i) - 1; j++) {
            ind.push_back(l);
            ind.push_back(r);
        }
        ind.push_back(r);   // make results independent
    }
    int res = simpleresult - ask(ind);
    vector<char> ans(sz);
    for (int i = 0; i < sz; i++) {
        char c;
        if (res & (1 << i)) {
            c = ')';
        }
        else c = '(';
        ans[i] = c;
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> every(n);
    iota(every.begin(), every.end(), 1);
    int all = ask(every);
    int l, r;   // (l, r) should be "()"
    if (all == 0) {
        l = n;
        r = 1;
    }
    else {
        int lo = 1, hi = n;
        while (lo < hi) {
            int med = lo + (hi - lo) / 2;
            // ask everything from 1 to med
            vector<int> pref(med);
            iota(pref.begin(), pref.end(), 1);
            int res = ask(pref);
            if (res == 0) {
                lo = med + 1;
            }
            else {
                // r > 0
                hi = med;
            }
        }
        l = lo - 1;
        r = lo;
    }
    string ans(n, '.');
    for (int i = 1; i <= n; ) {
        vector<int> toask;
        for (int j = i; j <= n && j < i + 8; j++) {
            toask.push_back(j);
        }
        vector<char> res = handle(toask, l, r);
        for (int j = 0; j < int(toask.size()); j++) {
            ans[toask[j] - 1] = res[j];
        }
        i = toask.back() + 1;
    }
    finish(ans);
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
