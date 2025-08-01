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

string handle_zero(int n) {
    string ans(n, '.');
    vector<int> cur;
    int lo = 1, hi = n - 1;
    while (lo < hi) {
        int med = lo + (hi - lo + 1) / 2;
        int r = ask({n, med});
        if (r == 0) {
            // on the right side
            hi = med - 1;
        }
        else {
            lo = med;
        }
    }
    // lo is the last ")"
    return string(lo, ')') + string(n - lo, '(');
}

pair<char,char> handle(int i, int l, int r) {
    int score = ask({l, i, i + 1, i, i + 1, r, r});
    if (score == 1) {
        return {')', ')'};
    }
    else if (score == 2) {
        return {'(', '('};
    }
    else if (score == 4) {
        return {'(', ')'};
    }
    else {
        assert(score == 6);
        return {')', '('};
    }
}

char handle_edge(int left, int other) {
    int r = ask({left, other});
    char c;
    if (r == 0) {
        c = '(';   
    }
    else {
        c = ')';
    }
    return c;
}

void solve() {
    int n;
    cin >> n;
    vector<int> every(n);
    iota(every.begin(), every.end(), 1);
    int all = ask(every);
    string ans;
    if (all == 0) {
        ans = handle_zero(n);
    }
    else {
        int lo = 1, hi = n;
        while (lo < hi) {
            int med = lo + (hi - lo) / 2;
            // ask everything from 1 to med
            vector<int> pref(med);
            iota(pref.begin(), pref.end(), 1);
            int r = ask(pref);
            if (r == 0) {
                lo = med + 1;
            }
            else {
                // r > 0
                hi = med;
            }
        }
        // (l, r) should be "()"
        int l = lo - 1;
        int r = lo;
        // based on this, we extract everything else
        ans = string(n, '.');
        ans[l - 1] = '(';
        ans[r - 1] = ')';
        for (int i = 1; i + 1 < l; i += 2) {
            auto [iv, jv] = handle(i, l, r);
            ans[i - 1] = iv;
            ans[i + 1 - 1] = jv;
        }
        for (int i = r + 1; i + 1 <= n; i += 2) {
            auto [iv, jv] = handle(i, l, r);
            ans[i - 1] = iv;
            ans[i + 1 - 1] = jv;
        }

        // 2 edge cases: just before l and just before n
        if (l % 2 == 0) {
            ans[l - 1 - 1] = handle_edge(l, l - 1);
        }
        if ((n - r) % 2 == 1) {
            ans[n - 1] = handle_edge(l, n);
        }
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
