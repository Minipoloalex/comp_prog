#include <bits/stdc++.h>
using namespace std;

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


void solve() {
    string t, p;
    cin >> t >> p;
    int ans = 0;
    string together = p + '#' + t;
    kmpPreprocess(together);
    for (int i = 0; i < int(kmp.size()); i++) {
        if (kmp[i] == int(p.size())) {
            // cout << "Match found at index " << i - int(p.size()) << " of together\n";
            // cout << "Match found at index " << i - 2 * int(p.size()) - 1 << " of text\n";
            // -1 accounts for the delimiter
            // kmp[i + 1] -> corresponds to index i of the string
            // i - p.size() -> gives starting index of match (i corresponds to S[i - 1])
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
