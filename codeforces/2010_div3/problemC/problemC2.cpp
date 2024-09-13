#include <bits/stdc++.h>
using namespace std;

vector<int> kmp;

void kmpPreprocess(const string &p) {
    int m = int(p.size());
    kmp.resize(m + 1);

    int l = -1, r = 0;
    kmp.at(0) = -1;
    while (r < m) {    // l < r
        while (l >= 0 && p[r] != p[l]) l = kmp.at(l);
        l++; r++;

        // Here, we have l >= 0 and r >= 1
        // Comparison of the i'th character corresponds to the (i + 1)'th position in the array)
        kmp.at(r) = l;
    }
}


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    #ifdef HELLO
    int t;
    cin >> t;
    while (t--) {
    #endif
    string s;
    cin >> s;
    int n = int(s.size());
    kmpPreprocess(s);

    #ifdef DEBUG
    for (int v: kmp) {
        cout << v << " ";
    }
    cout << endl;
    #endif

    if (kmp.back() > n / 2) {
        cout << "YES\n";
        cout << s.substr(0, kmp.back()) << '\n';
    }
    else {
        cout << "NO\n";
    }
    #ifdef HELLO
    }
    #endif
    return 0;
}
