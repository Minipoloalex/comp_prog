#include <bits/stdc++.h>
using namespace std;

void start(int64_t a) {
    cout << a << endl;
}
int ins(int64_t x) {
    cout << "I " << x << endl;
    int ret;
    cin >> ret;
    return ret;
}
int q(int64_t y) {
    cout << "Q " << y << endl;
    int ret;
    cin >> ret;
    if (ret == -1) exit(0);
    return ret;
}

void finish(int k, int64_t c) {
    cout << "A " << k << " " << c << endl;
}

void solve() {
    int n;
    cin >> n;
    auto bs = [&](int64_t l, int64_t r) {
        while (l < r) {
            int64_t m = l + (r - l + 1) / 2;
            int qans = q(m);
            if (qans == 1) {
                // means that number is on the right side
                l = m;
            }
            else {
                assert(qans == 0);
                r = m - 1; // means that number is on the left
            }
        }
        return l;
    };
    start(0);
    int begin_sz = ins(0);
    bool isand = begin_sz == 1;
    if (isand) {
        ins((1LL << n) - 1);
    }
    int64_t c = bs(1, (1LL << n) - 1);
    int k;
    if (isand) {
        k = 1;
    }
    else {
        if (c == ((1LL << n) - 1)) {
            // can't push 2^n-1 otherwise xor would lead to 0
            // set size would be same for both cases
            int sz_now = ins(1);
            if (sz_now == begin_sz) {
                // both 0 and 1 went to 2^n-1
                k = 2;
            }
            else {
                k = 3;
            }
        }
        else {
            ins((1LL << n) - 1); // could probably just do it with this using the size
            // which would be n + 2 queries
            int isor = q((1LL << n) - 1) == 1;
            k = isor ? 2 : 3;   // k = 3 (there was no 2^n-1 because it's XOR)
        }
    }
    finish(k, c);
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
