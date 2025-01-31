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
    string s;
    cin >> s;
    kmpPreprocess(s);
    int n = int(s.size());
    int j = n;
    list<int> ans;
    while (kmp[j] > 0) {
        ans.push_front(kmp[j]); // want in ascending order (reverse of what we get here)
        j = kmp[j];
    }
    for (int a: ans) cout << a << " ";
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
