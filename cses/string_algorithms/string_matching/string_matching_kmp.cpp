#include <bits/stdc++.h>
using namespace std;

int ans = 0;

// Pattern preprocessed (back jumps): [-1, 0, ...]
vector<int> kmp;

// pattern p
void kmpPreprocess(const string &p) {
    int sz = int(p.size());
    kmp.resize(sz + 1);

    int l = -1, r = 0;
    kmp[0] = -1;
    while (r < sz) {    // l < r
        while (l >= 0 && p[r] != p[l]) l = kmp[l];
        l++; r++;

        // Here, we have l >= 0 and r >= 1
        // Comparison of the i'th character corresponds to
        // the (i + 1)'th position in the array
        kmp[r] = l;
    }
}

// pattern p, text t (must call kmpPreprocess(p) before)
void kmpSearch(const string &p, const string &t) {
    int n = int(t.size());
    int m = int(p.size());
    int i = 0, j = 0;   // i loops through text, j through pattern
    while (i < n) {
        while (j >= 0 && (t[i] != p[j])) j = kmp[j];
        i++; j++;
        if (j == m) {
            ans++;
            j = kmp[j];  // continue looking for more matches 
        }
    }
}
void solve() {
    string t, p;
    cin >> t >> p;
    kmpPreprocess(p);
    kmpSearch(p, t);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
