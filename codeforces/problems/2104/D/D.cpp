#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e7);
bitset<MAX> bs;
vector<int> p;
vector<int64_t> pref;

void sieve() {
    bs.set();
    bs[0] = bs[1] = 0;
    for (int i = 2; i < MAX; i++) {
        if (bs[i]) {
            p.push_back(i);
            for (int j = i; j < MAX; j += i) {
                bs[j] = 0;
            }
        }
    }
}
void prepare_primes() {
    sieve();
    pref.assign(p.size() + 1, 0);
    for (int i = 0; i < int(p.size()); i++) {
        pref[i + 1] = pref[i] + p[i];
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    sort(a.begin(), a.end());
    int64_t sm = accumulate(a.begin(), a.end(), 0LL);
    int sz, i;
    for (sz = n, i = 0; sz >= 1; sz--, i++) {
        if (sm >= pref[sz]) {
            break;
        }
        sm -= a[i];
    }
    cout << n - sz << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    prepare_primes();
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
